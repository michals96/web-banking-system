#include "WebBankingApplication.h"
#include <Wt/WApplication.h>
#include <Wt/WText.h>

WebBankingApplication::WebBankingApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env),
	  Wt::WContainerWidget()
{
	setTitle("Web banking system");
	messageResourceBundle().use(appRoot() + "strings");
	useStyleSheet("css/FrontPage.css");
	
	std::unique_ptr<Wt::WText> title(Wt::cpp14::make_unique<Wt::WText>("<h1>Web Banking System</h1>"));

	root()->addWidget(std::move(title));
}