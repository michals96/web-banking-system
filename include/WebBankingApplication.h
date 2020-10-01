#pragma once
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include "../include/Session.h"

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
	
	Session session;

	void onAuthEvent();
	void showUserPanel();
};
