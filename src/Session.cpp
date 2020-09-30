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

#ifndef WT_WIN32
#include <unistd.h>
#endif

namespace dbo = Wt::Dbo;

namespace {

	class MyOAuth : public std::vector<const Auth::OAuthService*>
	{
	public:
		~MyOAuth()
		{
			for (unsigned i = 0; i < size(); ++i)
				delete (*this)[i];
		}
	};

	Auth::AuthService myAuthService;
	Auth::PasswordService myPasswordService(myAuthService);
	MyOAuth myOAuthServices;
}

Session::Session()
{
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
