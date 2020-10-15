#pragma once
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include "../include/Session.h"
#include "../include/ListAccountsWidget.h"

using namespace Wt;

class Session;
class WebBankingWidget;

class WebBankingApplication : public Wt::WContainerWidget
{
public:
	WebBankingApplication();
	void handleInternalPath(const std::string& internalPath);
	

private:
	WebBankingWidget     *panel;
	WStackedWidget       *mainStack;
	WContainerWidget     *userLinks;
	WContainerWidget	 *adminLinks;
	ListAccountsWidget   *accounts;

	WAnchor* balanceAnchor;
	WAnchor* transactionAnchor;
	WAnchor* listUsersAnchor;

	Session session;

	void onAuthEvent();
	void showUserPanel();
	void showAllAccounts();
};
