#ifndef WEBBANKINGAPPLICATION_H_
#define WEBBANKINGAPPLICATION_H_

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include "Session.h"

class Session;

class WebBankingApplication : public Wt::WContainerWidget
{
public:
	WebBankingApplication();

private:
	Session session;

	void onAuthEvent();
};

#endif //WEBBANKINGAPPLICATION_H_