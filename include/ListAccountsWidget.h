#pragma once

#include <Wt/WContainerWidget.h>

using namespace Wt;

class Session;

class ListAccountsWidget : public WContainerWidget
{
public:
	ListAccountsWidget(Session* session);
	void update();

private:
	Session* session_;
};