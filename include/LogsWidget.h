#pragma once
#include <Wt/WContainerWidget.h>

using namespace Wt;

class Session;

class LogsWidget : public WContainerWidget
{
public:
	LogsWidget(Session* session);
	void update();

private:
	Session* session_;
};
