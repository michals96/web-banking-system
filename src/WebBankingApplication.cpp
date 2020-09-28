#include "WebBankingApplication.h"
#include <Wt/WText.h>

WebBankingApplication::WebBankingApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env),
	  Wt::WContainerWidget()
{


	setTitle("Web banking system");

	std::unique_ptr<Wt::WText> title(Wt::cpp14::make_unique<Wt::WText>("<h1>Web Banking System</h1>"));

	useStyleSheet("css/FrontPage.css");

	root()->addWidget(std::move(title));
}