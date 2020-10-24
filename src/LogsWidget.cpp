#include <Wt/WText.h>
#include <Wt/Dbo/Dbo.h>

#include "../include/LogsWidget.h"
#include "../include/Session.h"
#include "../include/User.h"

using namespace Wt;

LogsWidget::LogsWidget(Session* session) :
	WContainerWidget(),
	session_(session)
{
	setContentAlignment(AlignmentFlag::Center);
	setStyleClass("showLogs");
}

void LogsWidget::update()
{
	clear();

	this->addWidget(cpp14::make_unique<WText>("<h2>Here are service logs</h2>"));
}
