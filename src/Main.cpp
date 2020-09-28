#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "Hello.h"
#include "WebBankingApplication.h"
#include "HelloApplication.h"



int main(int argc, char** argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return Wt::cpp14::make_unique<WebBankingApplication>(env);
        });
}