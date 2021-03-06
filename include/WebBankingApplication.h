#pragma once
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include "../include/Session.h"
#include "../include/ListAccountsWidget.h"
#include "../include/UserBalanceWidget.h"
#include "../include/TransactionsWidget.h"
#include "../include/LogsWidget.h"

using namespace Wt;

class Session;
class UserBalanceWidget;
class ListAccountsWidget;

class WebBankingApplication : public Wt::WContainerWidget
{
public:
	WebBankingApplication();
	void handleInternalPath(const std::string& internalPath);
	
private:
	UserBalanceWidget    *userBalance;
	WStackedWidget       *mainStack;
	WContainerWidget     *userLinks;
	WContainerWidget	 *adminLinks;
	ListAccountsWidget   *accounts;
	TransactionsWidget   *transactions;
	LogsWidget			 *logs;

	WAnchor* balanceAnchor;
	WAnchor* transactionAnchor;
	WAnchor* listUsersAnchor;
	WAnchor* serviceLogsAnchor;

	Session session;

	void onAuthEvent();
	void showUserBalance();
	void showAllAccounts();
	void showTransactionPanel();
	void showServiceLogs();
};
