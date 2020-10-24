#include <Wt/WText.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WGroupBox.h>

#include "../include/UserBalanceWidget.h"
#include "../include/Session.h"
#include "../include/User.h"

using namespace Wt;

UserBalanceWidget::UserBalanceWidget(Session* session):
	WContainerWidget(),
	session_(session)
{
	setContentAlignment(AlignmentFlag::Center);
	setStyleClass("showUserBalance");
}

void UserBalanceWidget::update()
{
	clear();

	std::string userName = session_->userName();
    int userBalance = 0;

	std::vector<User> top = session_->topUsers(5);

    for (auto& user : top) {

        if (user.name == userName) {
            userBalance = user.balance;
        }
    }
	
	auto groupBox = Wt::cpp14::make_unique<Wt::WGroupBox>(userName + " balance");
	groupBox->addStyleClass("centered-example");

	std::string userBalanceStr = std::to_string(userBalance);
	groupBox->addNew<Wt::WText>("<h2>" + userBalanceStr + "$</h2>");
	this->addWidget(std::move(groupBox));
}
