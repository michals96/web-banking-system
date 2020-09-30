#include "WebBankingApplication.h"
#include "Session.h"

#include <Wt/WApplication.h>
#include <Wt/WServer.h>

using namespace Wt;

std::unique_ptr<WApplication> createApplication(const WEnvironment& env)
{
    auto app = cpp14::make_unique<WApplication>(env);

    app->setTitle("Web Banking App");

    app->messageResourceBundle().use(app->appRoot() + "strings");

    app->useStyleSheet("css/FrontPage.css");

    app->root()->addWidget(cpp14::make_unique<WebBankingApplication>());

    return app;
}

int main(int argc, char** argv)
{
    try {
        WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(EntryPointType::Application, createApplication);

        server.run();
    }
    catch (WServer::Exception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}