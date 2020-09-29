#pragma once
#include "Session.h"
#include <Wt/Auth/Login.h>

class Session
{
public:
	Wt::Auth::Login& login();

private:
	Wt::Auth::Login login_;
};

