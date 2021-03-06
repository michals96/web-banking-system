#include <Wt/WText.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WAny.h>
#include <Wt/WBreak.h>
#include <Wt/WGroupBox.h>

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

	auto groupBox = Wt::cpp14::make_unique<Wt::WGroupBox>("Service logs");
	groupBox->addStyleClass("centered-example");

	std::ifstream file("logs.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			groupBox->addNew<Wt::WText>(line.c_str());
		}

		this->addWidget(std::move(groupBox));

		file.close();
	}
}
