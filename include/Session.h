#pragma once
#include <Wt/Auth/Login.h>

#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include<vector>
#include "User.h"

using namespace Wt;

typedef Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

class Session
{
public:
	Session();
	~Session();

	Wt::Auth::Login& login();
	Auth::AbstractUserDatabase& users();
	std::string userName() const;

	static const Auth::AuthService& auth();
	static const Auth::AbstractPasswordService& passwordAuth();
	static const std::vector<const Auth::OAuthService*>& oAuth();

private:
	Wt::Auth::Login login_;
	std::unique_ptr<UserDatabase> users_;
};

