// session.cpp - blpapi Session	class
// Copyright KALX, LLC. All rights reserved. No warranty made.
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
	.FunctionHelp("Return a handle to an Open Bloomberg Session.")
);
HANDLEX WINAPI
xll_blp_session(HANDLEX so)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		if (so) {
			handle<SessionOptions> hso(so,false);
			ensure (hso);
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

static AddIn xai_blp_session_open_service(
	Function(XLL_HANDLE, "?xll_blp_session_open_service", "BLP.SESSION.OPEN.SERVICE")
	.Arg(XLL_HANDLE, "Session", "is a handle to a session.")
	.Arg(XLL_CSTRING, "Uri", "is the name of the Service to open. ")
	.Category(CATEGORY)
	.FunctionHelp("Open the service specified by Uri and return the Session handle.")
	.Documentation(
        "Attempt to open the service identified by the specified "
        "'uri' and block until the service is either opened "
        "successfully or has failed to be opened. Return Session handle if "
        "the service is opened successfully and 0 if the "
        "service cannot be successfully opened. "
        "</para><para>"
        "The 'uri' must contain a fully qualified service name. That "
        "is, it must be of the form \"//&lt;namespace&gt;/&lt;service-name&gt;\". "
        "</para><para>"
        "Before openService() returns a SERVICE_STATUS Event is "
        "generated. If this is an asynchronous Session then this "
        "Event may be processed by the registered EventHandler "
        "before openService() has returned. "
	)
);
HANDLEX WINAPI
xll_blp_session_open_service(HANDLEX session, const char* service)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Session> hs(session,false);
		ensure (hs);
		ensure (hs->openService(service));

		h = session;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return h;
}

static AddIn xai_blp_session_get_service(
	Function(XLL_HANDLE, "?xll_blp_session_get_service", "BLP.SESSION.GET.SERVICE")
	.Arg(XLL_HANDLE, "Session", "is a handle to a session.")
	.Arg(XLL_CSTRING, "Uri", "is the name of the Service to get. ")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to the Service specified by the Uri.")
	.Documentation(
        "The 'uri' must contain a fully qualified service name. That "
        "is, it must be of the form \"//&lt;namespace&gt;/&lt;service-name&gt;\". "
		"</para><para>"
		"If the service identified by the specified 'uri' is not "
        "open already then an InvalidStateException is thrown. "
	)
);
HANDLEX WINAPI
xll_blp_session_get_service(HANDLEX session, const char* service)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Session> hs(session,false);
		ensure (hs);
		
		Service svc = hs->getService(service); // lives until Session is terminated

		h = p2h<Service>(&svc);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return h;
}


static AddInX xai_blp_session_send_request(
	FunctionX(XLL_HANDLE, "?xll_blp_session_send_request", "BLP.SESSION.SEND.REQUEST")
	.Arg(XLL_HANDLE, "Session", "is a handle to a Session.")
	.Arg(XLL_HANDLE, "Request", "is a handle to a Request.")
	.Arg(XLL_HANDLE, "CorrelationID", "is a handle to a CorrelationID or an integer. ")
	.Category(CATEGORY)
	.FunctionHelp(_T("Description."))
#ifdef _DEBUG
	.Documentation(_T("Documentation."))
#endif
	);
HANDLEX WINAPI
xll_blp_session_send_request(HANDLEX session, HANDLEX request, HANDLEX cid)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Session> hsession(session,false);
		ensure (hsession);
		handle<Request> hrequest(request,false);
		ensure (hrequest);
		handle<CorrelationId> hcid(cid,false);

		hsession->sendRequest(*hrequest, hcid ? *hcid : CorrelationId(static_cast<long long>(cid)));
		h = session;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return h;
}

static AddInX xai_blp_session_next_event(
	FunctionX(XLL_HANDLE, "?xll_blp_session_next_event", "BLP.SESSION.NEXT.EVENT")
	.Arg(XLL_HANDLE, "Session", "is a handle to a Session.")
	.Category(CATEGORY)
	.FunctionHelp(_T("Description."))
#ifdef _DEBUG
	.Documentation(_T("Documentation."))
#endif
	);
HANDLEX WINAPI
xll_blp_session_next_event(HANDLEX session)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Session> hsession(session,false);
		ensure (hsession);

		Event e = hsession->nextEvent();

		h = p2h<Event>(&e);
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
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return status;
}
*/