#include <Wt/WText.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBreak.h>
#include <Wt/WSlider.h>

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

	auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>();

	container->addNew<Wt::WText>("How much money do you want to transfer?");
	container->addNew<Wt::WBreak>();

	Wt::WSlider* slider = container->addNew<Wt::WSlider>();
	slider->resize(500, 50);
	slider->setTickPosition(Wt::WSlider::TickPosition::TicksAbove);
	slider->setTickInterval(10);
	slider->setMinimum(1);
	slider->setMaximum(2000);
	slider->setValue(1000);

	container->addNew<Wt::WBreak>();
	Wt::WText* out =
		container->addNew<Wt::WText>();

	slider->valueChanged().connect([=] {
		out->setText("AMOUNT: " + slider->valueText() + "$");
		});

	this->addWidget(std::move(container));

}
