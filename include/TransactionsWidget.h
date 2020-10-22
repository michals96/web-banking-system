#pragma once

#include <Wt/WContainerWidget.h>

using namespace Wt;

class Session;

class TransactionsWidget : public WContainerWidget
{
public:
	TransactionsWidget(Session* session);
	void update();

private:
	Session* session_;
};
