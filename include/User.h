#pragma once

#include <Wt/WDateTime.h>
#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/Auth/Dbo/AuthInfo.h>

using namespace Wt;
namespace dbo = Wt::Dbo;

class User;
typedef Auth::Dbo::AuthInfo<User> AuthInfo;
typedef dbo::collection< dbo::ptr<User> > Users;

class User
{
public:
	User();
    std::string name;
    int balance;
    dbo::collection<dbo::ptr<AuthInfo>> authInfos;

    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, balance, "balance");

        dbo::hasMany(a, authInfos, dbo::ManyToOne, "user");
    }
};

DBO_EXTERN_TEMPLATES(User);
