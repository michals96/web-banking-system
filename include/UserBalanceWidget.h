#pragma once
#include <Wt/WContainerWidget.h>

using namespace Wt;

class Session;

class UserBalanceWidget : public WContainerWidget
{
public:
	UserBalanceWidget(Session* session);

private:
	Session* session_;
};
