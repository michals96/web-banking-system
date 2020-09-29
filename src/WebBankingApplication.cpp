#include "WebBankingApplication.h"
#include <Wt/WApplication.h>
#include <Wt/WAnchor.h>
#include <Wt/WText.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/RegistrationModel.h>

WebBankingApplication::WebBankingApplication()
	: Wt::WContainerWidget()
{
	session.login().changed().connect(this, &WebBankingApplication::onAuthEvent);
	std::unique_ptr<Wt::WText> title(Wt::cpp14::make_unique<Wt::WText>("<h1>Web Banking System</h1>"));

	addWidget(std::move(title));

}

void WebBankingApplication::onAuthEvent()
{

}