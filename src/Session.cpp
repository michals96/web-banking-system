#include "Session.h"

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
	Auth::AuthService myAuthService;
	Auth::PasswordService myPasswordService(myAuthService);
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
