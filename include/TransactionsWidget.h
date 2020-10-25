#pragma once

#include <Wt/WContainerWidget.h>

using namespace Wt;

class Session;

class TransactionsWidget : public WContainerWidget
{
public:
	TransactionsWidget() {}
	TransactionsWidget(Session* session);
	void update();
	void log(std::string tgtName, std::string srcName, int amount, bool succeddedTransaction);
	std::string currentDateTime();

private:
	Session* session_;
};
