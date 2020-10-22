#include <Wt/WText.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBreak.h>
#include <Wt/WSlider.h>
#include <Wt/WAny.h>
#include <Wt/WComboBox.h>
#include <Wt/WStringListModel.h>
#include <Wt/WBreak.h>
#include <Wt/WProgressBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WTimer.h>

#include "../include/TransactionsWidget.h"
#include "../include/Session.h"
#include "../include/User.h"

using namespace Wt;

TransactionsWidget::TransactionsWidget(Session* session) :
	WContainerWidget(),
	session_(session)
{
	setContentAlignment(AlignmentFlag::Center);
	setStyleClass("showTransactions");
}

void TransactionsWidget::update()
{
	clear();

	// --------------------------------------------

	std::vector<User> top = session_->topUsers(5);
	std::vector<User> transactionUsers;

	std::copy_if(top.begin(), top.end(), std::back_inserter(transactionUsers), [&](User u) { return u.name != "admin" && u.name != session_->userName(); });

	// --------------------------------------------

	auto amountContainer = Wt::cpp14::make_unique<Wt::WContainerWidget>();

	amountContainer->addNew<Wt::WText>("How much money do you want to transfer?");
	amountContainer->addNew<Wt::WBreak>();

	Wt::WSlider* slider = amountContainer->addNew<Wt::WSlider>();
	slider->resize(500, 50);
	slider->setTickPosition(Wt::WSlider::TickPosition::TicksAbove);
	slider->setTickInterval(10);
	slider->setMinimum(1);
	slider->setMaximum(2000);
	slider->setValue(1000);

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

	cb->setCurrentIndex(1); // Show 'Medium' initially.
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
		if (bar->value() < 10) {
			intervalTimer->start();
			startButton->setText("Resume");
		}

		startButton->disable();
		stopButton->enable();
		resetButton->disable();
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
			stopButton->clicked().emit(Wt::WMouseEvent());
			startButton->disable();
			this->addWidget(cpp14::make_unique<WBreak>());
			this->addWidget(std::move(cpp14::make_unique<WText>("Transfer complete!")));

		}
		});

	this->addWidget(std::move(container));
}	
