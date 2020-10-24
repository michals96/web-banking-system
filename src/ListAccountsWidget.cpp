#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WAny.h>

#include "../include/ListAccountsWidget.h"
#include "../include/Session.h"

using namespace Wt;

ListAccountsWidget::ListAccountsWidget(Session* session):
	WContainerWidget(),
	session_(session)
{
	setContentAlignment(AlignmentFlag::Center);
	setStyleClass("listAccounts");
}

void ListAccountsWidget::update()
{
	clear();

    this->addWidget(cpp14::make_unique<WText>("<h2> All accounts in the bank </h2>"));

    int ranking = session_->findId();

    std::vector<User> top = session_->topUsers(5);

    WTable* table = this->addWidget(cpp14::make_unique<WTable>());

    table->elementAt(0, 0)->addWidget(cpp14::make_unique<WText>("ID"));
    table->elementAt(0, 1)->addWidget(cpp14::make_unique<WText>("Name"));
    table->elementAt(0, 2)->addWidget(cpp14::make_unique<WText>("Balance"));
    table->setHeaderCount(1);

    int formerScore = -1;
    int rank = 0;
    for (auto& user : top) {

        if (user.balance != formerScore) {
            formerScore = user.balance;
            ++rank;
        }

        int row = table->rowCount();
        table->elementAt(row, 0)->addWidget(cpp14::make_unique<WText>(asString(rank)));
        table->elementAt(row, 1)->addWidget(cpp14::make_unique<WText>(user.name));
        table->elementAt(row, 2)->addWidget(cpp14::make_unique<WText>(asString(user.balance)));

        if (session_->login().loggedIn() && session_->userName() == user.name)
            table->rowAt(row)->setId("self");
    }
}