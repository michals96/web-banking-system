#include <Wt/WText.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WTable.h>
#include <Wt/WAny.h>
#include <Wt/WBreak.h>

#include "../include/LogsWidget.h"
#include "../include/Session.h"
#include "../include/User.h"

#include <fstream>

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

	std::ifstream file("logs.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			this->addWidget(cpp14::make_unique<WText>(line.c_str()));
			this->addWidget(cpp14::make_unique<WBreak>());
		}
		file.close();
	}
}
