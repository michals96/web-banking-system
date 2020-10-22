#include "../include/UserBalanceWidget.h"
#include "../include/Session.h"

using namespace Wt;

UserBalanceWidget::UserBalanceWidget(Session* session):
	WContainerWidget(),
	session_(session)
{
	setContentAlignment(AlignmentFlag::Center);
	setStyleClass("showUserBalance");
}
