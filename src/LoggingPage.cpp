#include "LoggingPage.h"
#include <Wt/WText.h>

LoggingPage::LoggingPage():
	WContainerWidget()
{
	std::unique_ptr<Wt::WText> title(Wt::cpp14::make_unique<Wt::WText>("<h1>A Witty game: Hangman</h1>"));
}