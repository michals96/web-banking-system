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
#include "../include/WebBankingWidget.h"

WebBankingApplication::WebBankingApplication()
	: Wt::WContainerWidget()
{
	session.login().changed().connect(this, &WebBankingApplication::onAuthEvent);

	std::unique_ptr<Wt::Auth::AuthModel> authModel
		= Wt::cpp14::make_unique<Wt::Auth::AuthModel>(Session::auth(), session.users());

	authModel->addPasswordAuth(&Session::passwordAuth());
	authModel->addOAuth(Session::oAuth());

	std::unique_ptr<Auth::AuthWidget> authWidget
		= cpp14::make_unique<Auth::AuthWidget>(session.login());
	auto authWidgetPtr = authWidget.get();
	authWidget->setModel(std::move(authModel));
	authWidget->setRegistrationEnabled(true);

	std::unique_ptr<Wt::WText> title(Wt::cpp14::make_unique<Wt::WText>("<h1 class='frontTitle'>Web Banking Application</h1>"));

	addWidget(std::move(title));

	addWidget(std::move(authWidget));

	// Here we can add new stacks like userStack, adminStack etc
	mainStack = new WStackedWidget();
	mainStack->setStyleClass("bankingStack");
	addWidget(std::unique_ptr<WStackedWidget>(mainStack));

	WApplication::instance()->internalPathChanged()
		.connect(this, &WebBankingApplication::handleInternalPath);

	authWidgetPtr->processEnvironment();
}

void WebBankingApplication::onAuthEvent()
{

}

void WebBankingApplication::handleInternalPath(const std::string& internalPath)
{
	if (session.login().loggedIn()) {
		if (internalPath == "/userPanel")
		{
			showUserPanel();
		}
		// Handling admin panel
		else if (internalPath == "adminPanel")
		{
			// showAdminPanel();
		}
	}
}

void WebBankingApplication::showUserPanel()
{
	if (!panel)
	{
		panel = mainStack->addWidget(cpp14::make_unique<WebBankingWidget>(session.userName()));
	}

	mainStack->setCurrentWidget(panel);
}
