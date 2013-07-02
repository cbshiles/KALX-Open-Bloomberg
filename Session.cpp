// session.cpp - blpapi Session class
#pragma warning(disable: 4244 4127 4100)
#include "blpapi_session.h"
#include "xllblp.h"

using namespace BloombergLP;
using namespace blpapi;
using namespace xll;

static AddIn xai_blp_session(
	Function(XLL_HANDLE, "?xll_blp_session", "BLP.SESSION")
	.Arg(XLL_HANDLE, "Options", "is a handle returned by BLP.SESSION.OPTIONS", 0)
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to and Open Bloomberg Session.")
);
HANDLEX WINAPI
xll_blp_session(HANDLEX so)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		if (so) {
			handle<SessionOptions> hso(so);
			ensure (so);
			handle<Session> hs(new Session(*hso));

			h = hs.get();
		}
		else {
			handle<Session> hs(new Session());

			h = hs.get();
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return h;
}
/*
static AddIn xai_blp_session_status(
	Function(XLL_CSTRING, "?xll_session_status", "BLP.SESSION.STATUS")
	.Arg(XLL_HANDLE, "Session", "is a handle to a Session.")
	.Volatile()
	.Category(CATEGORY)
	.FunctionHelp("Return the current status of a Session.")
);
const char* WINAPI
xll_blp_session_status(HANDLEX hSession)
{
#pragma XLLEXPORT
	const char* status = "UNKNOWN";

	try {
		handle<Session> hsession(hSession);
		ensure (hsession);

		SubscriptionIterator si(hsession);
		switch (si.subscriptionStatus()) {
		case Session::UNSUBSCRIBED:
            // No longer active, terminated by API.
			status = "UNSUBSCRIBED";
			break;
		case Session::SUBSCRIBING:
            // Initiated but no updates received.
			status = "SUBSCRIBING";
			break;
		case Session::SUBSCRIBED:
            // Updates are flowing.
			status = "SUBSCRIBED";
			break;
		case Session::CANCELLED:
            // No longer active, terminated by Application.
			status = "CANCELLED";
			break;
		case Session::PENDING_CANCELLATION:
			status = "PENDING_CANCELLATION";
			break;
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return status;
}
*/