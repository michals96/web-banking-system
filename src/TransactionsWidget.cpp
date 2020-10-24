#include <Wt/WText.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBreak.h>
#include <Wt/WSlider.h>
#include <Wt/WAny.h>
#include <Wt/WComboBox.h>
#include <Wt/WStringListModel.h>
#include <Wt/WProgressBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WTimer.h>
#include <Wt/WMessageBox.h>

#include "../include/TransactionsWidget.h"
#include "../include/Session.h"
#include "../include/User.h"

#include <fstream>


using namespace Wt;

TransactionsWidget::TransactionsWidget(Session* session) :
	WContainerWidget(),
	session_(session)
{
	setContentAlignment(AlignmentFlag::Center);
	setStyleClass("showTransactions");
}

std::string TransactionsWidget::currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

void TransactionsWidget::log(std::string tgtName, std::string srcName, int amount, bool succeddedTransaction)
{
	std::ofstream outfile;
	outfile.open("logs.txt", std::ios_base::app);

	if (succeddedTransaction)
	{
		outfile << "<h3>[" + currentDateTime() + "] " + srcName + " transferred " + std::to_string(amount) + "$ to " + tgtName + "</h3>\n";
	}
	else
	{
		outfile << "<h3 style='color:Tomato;'>[" + currentDateTime() + "] " + srcName + " failed to wire " + std::to_string(amount) + "$ to" + tgtName + "</h3>\n";
	}
}
void TransactionsWidget::update()
{
	clear();

	std::vector<User> top = session_->topUsers(5);

	User currentUser;

	for (auto& user : top) {
		if (user.name == session_->userName()) {
			currentUser = user;
		}
	}
	
	std::vector<User> transactionUsers;

	std::copy_if(top.begin(), top.end(), std::back_inserter(transactionUsers), [&](User u) { return u.name != "admin" && u.name != session_->userName(); });

	auto amountContainer = Wt::cpp14::make_unique<Wt::WContainerWidget>();

	amountContainer->addNew<Wt::WText>("How much money do you want to transfer?");
	amountContainer->addNew<Wt::WBreak>();

	Wt::WSlider* slider = amountContainer->addNew<Wt::WSlider>();

	slider->resize(500, 50);
	slider->setTickPosition(Wt::WSlider::TickPosition::TicksAbove);
	slider->setTickInterval(1);
	slider->setMinimum(10);
	slider->setMaximum(currentUser.balance);
	slider->setValue(currentUser.balance/2);
	
	amountContainer->addNew<Wt::WBreak>();
	Wt::WText* out =
		amountContainer->addNew<Wt::WText>();

	slider->valueChanged().connect([=] {
		out->setText(" " + slider->valueText() + "$");
		});
	
	this->addWidget(std::move(amountContainer));

	this->addWidget(cpp14::make_unique<WBreak>());

	auto selectUserContainer = Wt::cpp14::make_unique<Wt::WContainerWidget>();

	auto cb = selectUserContainer->addNew<Wt::WComboBox>();

	for (auto& user : transactionUsers) {
		cb->addItem(user.name);
	}

	cb->setCurrentIndex(1);
	cb->setMargin(10, Wt::Side::Right);

	auto outText = selectUserContainer->addNew<Wt::WText>();
	outText->addStyleClass("help-block");

	cb->changed().connect([=] {
		outText->setText(Wt::WString("You selected {1}.")
			.arg(cb->currentText()));
		});

	this->addWidget(std::move(selectUserContainer));

	this->addWidget(cpp14::make_unique<WBreak>());

	auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>();
	container->setStyleClass("inline-buttons");

	Wt::WProgressBar* bar = container->addNew<Wt::WProgressBar>();
	bar->setRange(0, 10);

	this->addWidget(cpp14::make_unique<WBreak>());

	Wt::WPushButton* startButton = container->addNew<Wt::WPushButton>("Start");
	Wt::WPushButton* stopButton = container->addNew<Wt::WPushButton>("Stop");
	Wt::WPushButton* resetButton = container->addNew<Wt::WPushButton>("Reset");

	// Initially, only the start button is enabled.
	stopButton->disable();
	resetButton->disable();

	// setup an interval timer which generates a timeout() signal every second.
	auto intervalTimer = container->addChild(Wt::cpp14::make_unique<Wt::WTimer>());
	intervalTimer->setInterval(std::chrono::milliseconds(1000));

	startButton->clicked().connect([=] {

		if (currentUser.balance == 0)
		{
			Wt::StandardButton answer 
				= Wt::WMessageBox::show("Not enough cash", "<p> You don't have enough money!</p>", Wt::StandardButton::Ok);
		}

		if (slider->value() == currentUser.balance/2 && currentUser.balance != 0)
		{
			Wt::StandardButton answer
				= Wt::WMessageBox::show("Transfer amount not set", "<p> Please select money transfer amount!</p>", Wt::StandardButton::Ok);
		}
		else {

			std::string amountString = std::to_string(slider->value());

			Wt::StandardButton answer
				= Wt::WMessageBox::show("Transfer money",
					"<p>Do you want to trasfer " + amountString + "$ to " + transactionUsers[cb->currentIndex()].name + "?</p>",
					Wt::StandardButton::Ok | Wt::StandardButton::Cancel);

			if (answer == Wt::StandardButton::Ok) {
				if (bar->value() < 10) {
					intervalTimer->start();
					startButton->setText("Resume");
				}

				startButton->disable();
				stopButton->enable();
				resetButton->disable();
			}
			else {

			}
		}
		});

	stopButton->clicked().connect([=] {
		intervalTimer->stop();

		startButton->enable();
		stopButton->disable();
		resetButton->enable();
		});

	resetButton->clicked().connect([=] {
		bar->setValue(0.0);
		startButton->setText("Start");

		startButton->enable();
		stopButton->disable();
		resetButton->disable();
		});

	intervalTimer->timeout().connect([=] {
		bar->setValue(bar->value() + 1);
		if (bar->value() == 10) {
			session_->addToBalance(transactionUsers[cb->currentIndex()].name, session_->userName(), slider->value());
			log(transactionUsers[cb->currentIndex()].name, session_->userName(), slider->value(), true);
			stopButton->clicked().emit(Wt::WMouseEvent());
			startButton->disable();
			this->addWidget(cpp14::make_unique<WBreak>());
			this->addWidget(std::move(cpp14::make_unique<WText>("Transfer complete!")));

		}
		});

	this->addWidget(std::move(container));
}	
