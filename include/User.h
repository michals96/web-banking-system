#pragma once

#include <Wt/WDateTime.h>
#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/Auth/Dbo/AuthInfo.h>

using namespace Wt;
namespace dbo = Wt::Dbo;

class User;
typedef Auth::Dbo::AuthInfo<User> AuthInfo;

class User
{
public:
	User();

    template<class Action>
    void persist(Action& a)
    {
        /*dbo::field(a, gamesPlayed, "gamesPlayed");
        dbo::field(a, score, "score");
        dbo::field(a, lastGame, "lastGame");

        dbo::hasMany(a, authInfos, dbo::ManyToOne, "user");*/
    }
};

