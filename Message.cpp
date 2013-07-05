// Message.cpp - blpapi Message class
#pragma warning(disable: 4244 4127)
#include "blpapi_message.h"
#include "xllblp.h"

using namespace xll;
using namespace BloombergLP;
using namespace blpapi;

static AddIn xai_blp_message_type(
	Function(XLL_CSTRING, "?xll_blp_message_type", "BLP.MESSAGE.TYPE")
	.Arg(XLL_HANDLE, "Message", "is a handle to a Message. ")
	.Category(CATEGORY)
	.FunctionHelp("Return the type of Message.")
	.Documentation(
	)
);
const char* WINAPI
xll_blp_message_type(HANDLEX message)
{
#pragma XLLEXPORT
	static const char* s("");

	try {
		handle<Message> hm(message,false);
		ensure (hm);

		s = hm->messageType().string();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return s;
}

static AddIn xai_blp_message_topic_name(
	Function(XLL_CSTRING, "?xll_blp_message_topic_name", "BLP.MESSAGE.TOPIC.NAME")
	.Arg(XLL_HANDLE, "Message", "is a handle to a Message. ")
	.Category(CATEGORY)
	.FunctionHelp("Return the topic name of Message.")
	.Documentation(
	)
);
const char* WINAPI
xll_blp_message_topic_name(HANDLEX message)
{
#pragma XLLEXPORT
	static const char* s("");

	try {
		handle<Message> hm(message,false);
		ensure (hm);

		s = hm->topicName();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return s;
}

static AddIn xai_blp_message_correlation_id(
	Function(XLL_HANDLE, "?xll_blp_message_correlation_id", "BLP.MESSAGE.CORRELATION.ID")
	.Arg(XLL_HANDLE, "Message", "is a handle to a Message.")
	.Arg(XLL_USHORT, "Index", "is an optional Index. Default is 0. ")
	.Category(CATEGORY)
	.FunctionHelp("Return the correlation ID of Message.")
	.Documentation(
	)
);
HANDLEX WINAPI
xll_blp_message_correlation_id(HANDLEX message, USHORT i)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Message> hm(message,false);
		ensure (hm);

		CorrelationId cid = hm->correlationId(i);
		h = p2h<CorrelationId>(&cid);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return h;
}





