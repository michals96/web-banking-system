#include <Wt/WApplication.h>
#include <Wt/WAnchor.h>
#include <Wt/WText.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/RegistrationModel.h>
#include <string>

#include "../include/WebBankingApplication.h"
#include "../include/UserBalanceWidget.h"
#include "../include/TransactionsWidget.h"

using namespace Wt;

WebBankingApplication::WebBankingApplication()
	: Wt::WContainerWidget()
{
	session.login().changed().connect(this, &WebBankingApplication::onAuthEvent);

	std::unique_ptr<Wt::Auth::AuthModel> authModel
		= cpp14::make_unique<Wt::Auth::AuthModel>(Session::auth(), session.users());

	authModel->addPasswordAuth(&Session::passwordAuth());
	authModel->addOAuth(Session::oAuth());

	std::unique_ptr<Auth::AuthWidget> authWidget
		= cpp14::make_unique<Auth::AuthWidget>(session.login());
	auto authWidgetPtr = authWidget.get();
	authWidget->setModel(std::move(authModel));
	authWidget->setRegistrationEnabled(true);

	std::unique_ptr<Wt::WText> title(cpp14::make_unique<Wt::WText>("<h1 class='frontTitle'>Web Banking Application</h1>"));

	addWidget(std::move(title));

	addWidget(std::move(authWidget));

	// Here we can add new stacks like userStack, adminStack etc
	mainStack = new WStackedWidget();
	mainStack->setStyleClass("bankingStack");
	addWidget(std::unique_ptr<WStackedWidget>(mainStack));

	// Add user links
	userLinks = new WContainerWidget();
	userLinks->setStyleClass("links");
	userLinks->hide();
	addWidget(std::unique_ptr<WContainerWidget>(userLinks));

	balanceAnchor = userLinks->addWidget(cpp14::make_unique<WAnchor>("/balance", "See the balance"));
	balanceAnchor->setLink(WLink(LinkType::InternalPath, "/balance"));

	transactionAnchor = userLinks->addWidget(cpp14::make_unique<WAnchor>("/transaction", "Make a transaction"));
	transactionAnchor->setLink(WLink(LinkType::InternalPath, "/transaction"));

	// Add admin links
	adminLinks = new WContainerWidget();
	adminLinks->setStyleClass("links");
	adminLinks->hide();
	addWidget(std::unique_ptr<WContainerWidget>(adminLinks));

	listUsersAnchor = adminLinks->addWidget(cpp14::make_unique<WAnchor>("/accounts", "List all accounts"));
	listUsersAnchor->setLink(WLink(LinkType::InternalPath, "/accounts"));

	serviceLogsAnchor = adminLinks->addWidget(cpp14::make_unique<WAnchor>("/logs", "Service logs"));
	serviceLogsAnchor->setLink(WLink(LinkType::InternalPath, "/logs"));

	WApplication::instance()->internalPathChanged()
		.connect(this, &WebBankingApplication::handleInternalPath);

	authWidgetPtr->processEnvironment();
}

void WebBankingApplication::onAuthEvent()
{
	if (session.login().loggedIn() && session.userName() != "admin")
	{
		userLinks->show();
		handleInternalPath(WApplication::instance()->internalPath());
	}
	else if (session.login().loggedIn() && session.userName() == "admin")
	{
		adminLinks->show();
		handleInternalPath(WApplication::instance()->internalPath());
	}
	else 
	{
		handleInternalPath(WApplication::instance()->internalPath());
		mainStack->clear();
		userLinks->hide();
		adminLinks->hide();
	}
}

void WebBankingApplication::handleInternalPath(const std::string& internalPath)
{
	if (session.login().loggedIn() && session.userName() != "admin") 
	{
		if (internalPath == "/balance")
		{

			showUserBalance();
		}
		else if (internalPath == "/transaction")
		{

			showTransactionPanel();
		}
		else
		{
			WApplication::instance()->setInternalPath("/", true);
		}
	}
	else if (session.login().loggedIn() && session.userName() == "admin")
	{
		if (internalPath == "/accounts")
		{
			showAllAccounts();
		}
		else if (internalPath == "/logs")
		{
			showServiceLogs();
		}
		else
		{
			WApplication::instance()->setInternalPath("/", true);
		}
	}
	else if (session.login().loggedIn() == false)
	{
		WApplication::instance()->setInternalPath("", true);
	}

}

void WebBankingApplication::showServiceLogs()
{
	if (!logs)
		logs = mainStack->addWidget(cpp14::make_unique<LogsWidget>(&session));

	mainStack->setCurrentWidget(logs);
	logs->update();
}

void WebBankingApplication::showAllAccounts()
{
	if (!accounts)
		accounts = mainStack->addWidget(cpp14::make_unique<ListAccountsWidget>(&session));

	mainStack->setCurrentWidget(accounts);
	accounts->update();
}

void WebBankingApplication::showUserBalance()
{
	if (!userBalance)
		userBalance = mainStack->addWidget(cpp14::make_unique<UserBalanceWidget>(&session));

	mainStack->setCurrentWidget(userBalance);
	userBalance->update();
}

void WebBankingApplication::showTransactionPanel()
{
	if (!transactions)
		transactions = mainStack->addWidget(cpp14::make_unique<TransactionsWidget>(&session));

	mainStack->setCurrentWidget(transactions);
	transactions->update();
}
