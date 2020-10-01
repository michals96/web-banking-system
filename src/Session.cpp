#include "../include/Session.h"

#include "Wt/Auth/AuthService.h"
#include "Wt/Auth/HashFunction.h"
#include "Wt/Auth/PasswordService.h"
#include "Wt/Auth/PasswordStrengthValidator.h"
#include "Wt/Auth/PasswordVerifier.h"
#include "Wt/Auth/GoogleService.h"
#include "Wt/Auth/Dbo/AuthInfo.h"
#include "Wt/Auth/Dbo/UserDatabase.h"

#include <Wt/WApplication.h>
#include <Wt/WLogger.h>
#include <vector>
#include <string>

#ifndef WT_WIN32
#include <unistd.h>
#endif

namespace dbo = Wt::Dbo;

namespace {

	class MyOAuth : public std::vector<const Wt::Auth::OAuthService*>
	{
	public:
		~MyOAuth()
		{
			for (unsigned i = 0; i < size(); ++i)
				delete (*this)[i];
		}
	};

	Wt::Auth::AuthService myAuthService;
	Auth::PasswordService myPasswordService(myAuthService);
	MyOAuth myOAuthServices;
}

Session::Session()
{
	auto sqlite3 = cpp14::make_unique<Dbo::backend::Sqlite3>(WApplication::instance()->appRoot() + "WebBankingUserDatabase.db");
	sqlite3->setProperty("show-queries", "true");

	session_.setConnection(std::move(sqlite3));

	session_.mapClass<User>("user");
	session_.mapClass<AuthInfo>("auth_info");
	session_.mapClass<AuthInfo::AuthIdentityType>("auth_identity");
	session_.mapClass<AuthInfo::AuthTokenType>("auth_token");

	users_ = cpp14::make_unique<UserDatabase>(session_);

	dbo::Transaction transaction(session_);
	try {
		session_.createTables();

		Auth::User guestUser = users_->registerNew();
		guestUser.addIdentity(Auth::Identity::LoginName, "guest");
		myPasswordService.updatePassword(guestUser, "guest");

		log("info") << "Database created";
	}
	catch (...) {
		log("info") << "Using existing database";
	}

	transaction.commit();
}

void Session::configureAuth()
{
	myAuthService.setAuthTokensEnabled(true, "hangmancookie");
	myAuthService.setEmailVerificationEnabled(true);

	std::unique_ptr<Auth::PasswordVerifier> verifier
		= cpp14::make_unique<Auth::PasswordVerifier>();
	verifier->addHashFunction(cpp14::make_unique<Auth::BCryptHashFunction>(7));

#ifdef HAVE_CRYPT
	// We want to still support users registered in the pre - Wt::Auth
	verifier->addHashFunction(cpp14::make_unique<UnixCryptHashFunction>());
#endif

	myPasswordService.setVerifier(std::move(verifier));
	myPasswordService.setStrengthValidator(cpp14::make_unique<Auth::PasswordStrengthValidator>());
	myPasswordService.setAttemptThrottlingEnabled(true);

	if (Auth::GoogleService::configured())
		myOAuthServices.push_back(new Auth::GoogleService(myAuthService));
}

std::vector<User> Session::topUsers(int limit)
{
	dbo::Transaction transaction(session_);

	Users top = session_.find<User>().orderBy("score desc").limit(limit);

	std::vector<User> result;
	for (Users::const_iterator i = top.begin(); i != top.end(); ++i) {
		dbo::ptr<User> user = *i;
		result.push_back(*user);

		dbo::ptr<AuthInfo> auth = *user->authInfos.begin();
		std::string name = auth->identity(Auth::Identity::LoginName).toUTF8();

		result.back().name = name;
	}

	transaction.commit();

	return result;
}

Session::~Session()
{
}

Wt::Auth::Login& Session::login()
{
	return login_;
}

Auth::AbstractUserDatabase& Session::users()
{
	return *users_;
}

const Auth::AuthService& Session::auth()
{
	return myAuthService;
}

const Auth::AbstractPasswordService& Session::passwordAuth()
{
	return myPasswordService;
}

const std::vector<const Auth::OAuthService*>& Session::oAuth()
{
	return myOAuthServices;
}

std::string Session::userName() const
{
	if (login_.loggedIn())
		return login_.user().identity(Auth::Identity::LoginName).toUTF8();
	else
		return std::string();
}