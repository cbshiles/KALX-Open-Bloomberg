// Event.cpp - blpapi Event class
// Copyright KALX, LLC. All rights reserved. No warranty made.
#pragma warning(disable: 4244 4127)
#include "blpapi_event.h"
#include "xllblp.h"

using namespace BloombergLP;
using namespace blpapi;
using namespace xll;

XLL_ENUM_DOC(BLPAPI_EVENTTYPE_ADMIN, BLPAPI_EVENTTYPE_ADMIN, CATEGORY, "Admin event", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_ADMIN))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_SESSION_STATUS, BLPAPI_EVENTTYPE_SESSION_STATUS, CATEGORY, "Status updates for a session.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_SESSION_STATUS))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_SUBSCRIPTION_STATUS, BLPAPI_EVENTTYPE_SUBSCRIPTION_STATUS, CATEGORY, "Status updates for a subscription.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_SUBSCRIPTION_STATUS))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_REQUEST_STATUS, BLPAPI_EVENTTYPE_REQUEST_STATUS, CATEGORY, "Status updates for a request.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_REQUEST_STATUS))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_RESPONSE, BLPAPI_EVENTTYPE_RESPONSE, CATEGORY, "The final (possibly only) response to a request.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_RESPONSE))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_PARTIAL_RESPONSE, BLPAPI_EVENTTYPE_PARTIAL_RESPONSE, CATEGORY, "A partial response to a request.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_PARTIAL_RESPONSE))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_SUBSCRIPTION_DATA, BLPAPI_EVENTTYPE_SUBSCRIPTION_DATA, CATEGORY, "Data updates resulting from a subscription.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_SUBSCRIPTION_DATA))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_SERVICE_STATUS, BLPAPI_EVENTTYPE_SERVICE_STATUS, CATEGORY, "Status updates for a service.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_SERVICE_STATUS))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_TIMEOUT, BLPAPI_EVENTTYPE_TIMEOUT, CATEGORY, "An Event returned from nextEvent() if it timed out.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_TIMEOUT))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_AUTHORIZATION_STATUS, BLPAPI_EVENTTYPE_AUTHORIZATION_STATUS, CATEGORY, "Status updates for user authorization.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_AUTHORIZATION_STATUS))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_RESOLUTION_STATUS, BLPAPI_EVENTTYPE_RESOLUTION_STATUS, CATEGORY, "Status updates for a resolution operation.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_RESOLUTION_STATUS))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_TOPIC_STATUS, BLPAPI_EVENTTYPE_TOPIC_STATUS, CATEGORY, "Status updates about topics for service providers.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_TOPIC_STATUS))
XLL_ENUM_DOC(BLPAPI_EVENTTYPE_TOKEN_STATUS, BLPAPI_EVENTTYPE_TOKEN_STATUS, CATEGORY, "Status updates for a generate token request.", "Has value " XLL_STRZ_(BLPAPI_EVENTTYPE_TOKEN_STATUS))

static AddIn xai_blp_event_type(
	Function(XLL_LONG, "?xll_blp_event_type", "BLP.EVENT.TYPE")
	.Arg(XLL_HANDLE, "Event", "is a handle to an Event.")
	.Category(CATEGORY)
	.FunctionHelp("Return the type of an Event from the BLPAPI_EVENTTYPE_* enumeration.")
	.Documentation(
		"Return the basic data type used to represent a value in this "
        "element. The possible return values are enumerated in "
		"the <codeInline>BLPAPI_DATATYPE_*</codeInline> enumeration. "
	)
);
LONG WINAPI
xll_blp_event_type(HANDLEX event)
{
#pragma XLLEXPORT
	int l(0);

	try {
		handle<Event> he(event,false);
		ensure (he && he->isValid());

		l = he->eventType();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return l;
}

static AddIn xai_blp_message_iterator(
	Function(XLL_HANDLE, "?xll_blp_message_iterator", "BLP.MESSAGE.ITERATOR")
	.Arg(XLL_HANDLE, "Event", "is a handle to an Event.")
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to a MessageIterator of Event.")
	.Documentation(
    "An iterator over the Message objects within an Event.  "
    "</para><para>"
    "MessageIterator objects are used to process the individual "
    "Message objects in an Event received in an EventHandler, from "
    "EventQueue::nextEvent() or from Session::nextEvent(). "
    "</para><para>"
    "This class is used to iterate over each message in an "
    "Event. The user must ensure that the Event this iterator is "
    "created for is not destroyed before the iterator. "
	)
);
HANDLEX WINAPI
xll_blp_message_iterator(HANDLEX event)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Event> he(event,false);
		ensure (he && he->isValid());

		MessageIterator mi(*he);

		h = p2h<MessageIterator>(&mi);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return h;
}

static AddIn xai_blp_message_iterator_next(
	Function(XLL_BOOL, "?xll_blp_message_iterator_next", "BLP.MESSAGE.ITERATOR.NEXT")
	.Arg(XLL_HANDLE, "MessageIterator", "is a handle to a MessageIterator.")
	.Category(CATEGORY)
	.FunctionHelp("Advance to the next message and return 0 on success.")
	.Documentation(
        "Attempts to advance this MessageIterator to the next "
        "Message in this Event. Returns 0 on success and non-zero if "
        "there are no more messages. After next() returns 0 "
        "isValid() returns true, even if called repeatedly until the "
        "next call to next(). After next() returns non-zero then "
        "isValid() always returns false. "
	)
);
BOOL WINAPI
xll_blp_message_iterator_next(HANDLEX message_iterator)
{
#pragma XLLEXPORT
	BOOL b(1);

	try {
		handle<MessageIterator> hmi(message_iterator,false);
		ensure (hmi && hmi->isValid());

		b = hmi->next();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return b;
}

static AddIn xai_blp_message_iterator_message(
	Function(XLL_HANDLE, "?xll_blp_message_iterator_message", "BLP.MESSAGE.ITERATOR.MESSAGE")
	.Arg(XLL_HANDLE, "MessageIterator", "is a handle to a MessageIterator.")
	.Arg(XLL_BOOL, "Clone", "is an optional boolean indicating a copy of the Message will be returned. ")
	.Category(CATEGORY)
	.FunctionHelp("Returns the Message at the current position of this iterator.")
	.Documentation(
        "If the "
        "specified 'Clone' flag is set, the internal handle of the "
        "message returned is added a reference and the message can outlive "
        "the call to next(). If the 'Clone' flag is set to false, "
        "the use of message outside the scope of the iterator or after the "
        "next() call is undefined. "
        "The behavior is undefined if isValid() returns false. "
	)
);
HANDLEX WINAPI
xll_blp_message_iterator_message(HANDLEX message_iterator, BOOL clone)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<MessageIterator> hmi(message_iterator,false);
		ensure (hmi && hmi->isValid());

		Message m(hmi->message(clone != 0)); // pulls in __imp__g_blpapiFunctionEntries

		h = p2h<Message>(&m);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return h;
}
