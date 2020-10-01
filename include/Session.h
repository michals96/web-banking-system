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
	static void configureAuth();

	Session();
	~Session();

	Auth::AbstractUserDatabase& users();
	Wt::Auth::Login& login();
	
	std::vector<User> topUsers(int limit);

	std::string userName() const;

	static const Auth::AuthService& auth();
	static const Auth::AbstractPasswordService& passwordAuth();
	static const std::vector<const Auth::OAuthService*>& oAuth();

private:
	mutable Dbo::Session session_;
	Wt::Auth::Login login_;
	std::unique_ptr<UserDatabase> users_;
};

