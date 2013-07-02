// SessionOptions.cpp - Open Bloomberg SessionOptions
#pragma warning(disable: 4244 4127 4505)
#include "blpapi_sessionoptions.h"
#include "xllblp.h"

using namespace BloombergLP;
using namespace blpapi;
using namespace xll;

static AddIn xai_blp_session_options(
	Function(XLL_HANDLE, "?xll_blp_session_options", "BLP.SESSION.OPTIONS")
	.Arg(XLL_CSTRING, "Host", "is the name of the host or IPv4 address. Default value is \"127.0.0.1\".", "127.0.0.1")
	.Arg(XLL_USHORT, "Port", "is the port to connect to on the Host. Default is 8194", 8194)
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Specify the options which the user can specify when creating a session.")
	.Documentation("A common interface shared between publish and consumer sessions. ")
);
HANDLEX WINAPI
xll_blp_session_options(const char* host, USHORT port)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		SessionOptions* pso = new SessionOptions();
		if (host && *host)
			pso->setServerHost(host);
		if (port)
			pso->setServerPort(port);

		handle<SessionOptions> hso(pso);
		h = hso.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return h;
}

static AddIn xai_blp_session_options_connect_timeout(
	Function(XLL_HANDLE, "?xll_blp_session_options_connect_timeout", "BLP.SESSION.OPTIONS.CONNECT.TIMEOUT")
	.Arg(XLL_HANDLE, "Options", "is a handle returned by BLP.SESSION.OPTIONS")
	.Arg(XLL_USHORT, "Timeout", "is the optional connection timeout in milliseconds. ", 5000)
	.Category(CATEGORY)
	.FunctionHelp("Set or get the connection timeout when connecting to Open Bloomberg.")
	.Documentation(
		"Returns the <codeInline>Options</codeInline> handle if <codeInline>Timeout</codeInline> is specified, "
		"otherwise returns the current <codeInline>Timeout</codeInline>. "
		"The default <codeInline>Timeout</codeInline> is 5000 milliseconds. Behavior is not defined "
        "unless the specified <codeInline>Timeout</codeInline> is in range of [1 .. 120000] milliseconds. "
	)
);
HANDLEX WINAPI
xll_blp_session_options_connect_timeout(HANDLEX options, USHORT timeout)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<SessionOptions> hso(options);
		ensure (hso);

		if (timeout) {
			hso->setConnectTimeout(timeout);
			h = hso.get();
		}
		else {
			h = hso->connectTimeout();
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

static AddIn xai_blp_session_options_default_services(
	Function(XLL_LPOPER, "?xll_blp_session_options_default_services", "BLP.SESSION.OPTIONS.DEFAULT.SERVICES")
	.Arg(XLL_HANDLE, "Options", "is a handle returned by BLP.SESSION.OPTIONS.")
	.Arg(XLL_CSTRING, "Services", "is an optional semicolon separated list of services. ")
	.Category(CATEGORY)
	.FunctionHelp("Set or get the default services.")
	.Documentation("")
);
LPOPER WINAPI
xll_blp_session_options_default_services(HANDLEX options, const char* services)
{
#pragma XLLEXPORT
	static OPER result;

	try {
		handle<SessionOptions> hso(options);
		ensure (hso);

		if (services && *services) {
			hso->setDefaultServices(services);

			result = hso.get();
		}
		else {
			result = hso->defaultServices();
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return &result;
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