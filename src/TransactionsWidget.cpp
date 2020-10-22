#include <Wt/WText.h>
#include <Wt/Dbo/Dbo.h>

#include "../include/TransactionsWidget.h"
#include "../include/Session.h"
#include "../include/User.h"

using namespace Wt;

TransactionsWidget::TransactionsWidget(Session* session) :
	WContainerWidget(),
	session_(session)
{
	setContentAlignment(AlignmentFlag::Center);
	setStyleClass("showTransactions");
}

void TransactionsWidget::update()
{
	/* clear();

	std::string userName = session_->userName();
	int userBalance = 0;

	std::vector<User> top = session_->topUsers(5);

	for (auto& user : top) {

		if (user.name == userName) {
			userBalance = user.balance;
		}
	}

	std::string userBalanceStr = std::to_string(userBalance);

	this->addWidget(cpp14::make_unique<WText>("<h2>Hello " + userName + ",  your balance is " + userBalanceStr + "$</h2>"));*/
}
