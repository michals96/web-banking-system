#pragma once
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>

class WebBankingApplication : public Wt::WApplication, public Wt::WContainerWidget
{
public:
	WebBankingApplication(const Wt::WEnvironment& env);
};

