#ifndef WEBBANKINGAPPLICATION_H_
#define WEBBANKINGAPPLICATION_H_

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include "Session.h"

using namespace Wt;

class Session;

class WebBankingApplication : public Wt::WContainerWidget
{
public:
	WebBankingApplication();
	void handleInternalPath(const std::string& internalPath);

private:
	WStackedWidget* mainStack;
	Session session;

	void onAuthEvent();
};

#endif //WEBBANKINGAPPLICATION_H_