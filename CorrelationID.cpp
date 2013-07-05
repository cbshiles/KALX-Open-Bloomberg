// CorrelationID.cpp - blpapi CorrelationID class
// Copyright KALX, LLC. All rights reserved. No warranty made.
#include "blpapi_correlationid.h"
#include "xllblp.h"

using namespace xll;
using namespace BloombergLP;
using namespace blpapi;

XLL_ENUM_DOC(BLPAPI_CORRELATION_TYPE_UNSET, BLPAPI_CORRELATION_TYPE_UNSET, CATEGORY, "The CorrelationId is unset. That is it was created by the default CorrelationId constructor.", "The value is " XLL_STRZ_(BLPAPI_CORRELATION_TYPE_UNSET))
XLL_ENUM_DOC(BLPAPI_CORRELATION_TYPE_INT, BLPAPI_CORRELATION_TYPE_INT, CATEGORY, "CorrelationId was created from an integer supplied by the user.", "The value is " XLL_STRZ_(BLPAPI_CORRELATION_TYPE_INT))
XLL_ENUM_DOC(BLPAPI_CORRELATION_TYPE_POINTER, BLPAPI_CORRELATION_TYPE_POINTER, CATEGORY, "The CorrelationId was created from a pointer supplied by the user.", "The value is " XLL_STRZ_(BLPAPI_CORRELATION_TYPE_POINTER))
XLL_ENUM_DOC(BLPAPI_CORRELATION_TYPE_AUTOGEN, BLPAPI_CORRELATION_TYPE_AUTOGEN, CATEGORY, "The CorrelationId was created internally by API.", "The value is " XLL_STRZ_(BLPAPI_CORRELATION_TYPE_AUTOGEN))

static AddIn xai_blp_correlation_id(
	Function(XLL_HANDLE, "?xll_blp_correlation_id", "BLP.CORRELATION.ID")
	.Arg(XLL_LONG, "Id", "is the integer Id to use. ")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to a key used to identify individual subscriptions or requests.")
	.Documentation(
    "CorrelationId objects are passed to many of the Session object "
    "methods which initiate an asynchronous operations and are "
    "obtained from Message objects which are delivered as a result "
    "of those asynchronous operations. "
    "</para><para> "
    "When subscribing or requesting information an application has "
    "the choice of providing a CorrelationId they construct "
    "themselves or allowing the session to construct one for "
    "them. If the application supplies a CorrelationId it must not "
    "re-use the value contained in it in another CorrelationId "
    "whilst the original request or subscription is still active. "
    "</para><para> "
    "It is possible that an application supplied CorrelationId and a "
    "CorrelationId constructed by the API could return the same "
    "result for asInteger(). However, they will not compare equal "
    "using the defined operator== for CorrelationId and there is a "
    "consistent order defined using the defined operator&lt; for "
    "CorrelationId. "
    "</para><para> "
    "A CorrelationId constructed by an application can contain either "
    "</para><para> "
    "- a 64 bit integer, "
    "</para><para> "
    "- a simple pointer or "
    "</para><para> "
    "- a \"smart\" pointer object (for example, tr1::shared_ptr) "
    "</para><para> "
    "For 64 bit integers and simple pointers the values are copied "
    "when CorrelationIds are copied and compared when CorrelationIds "
    "are compared. "
    "</para><para> "
    "For \"smart\" pointers the API can accommodate smart pointer classes "
    "that meet the following restrictions. "
    "</para><para> "
    "- It is no more than sizeof(void*)*4 bytes in size. "
    "</para><para> "
    "- It is thread safe. "
    "</para><para> "
    "- It performs all its necessary management as a direct side "
    "effect of their copy constructor and destructor. "
    "</para><para> "
    "- Its contents are location independent (that is given two "
    "instances of a smart pointer s1 and s2 one can call std::swap(s1, s2) ). "
    "</para><para> "
    "The API will embed a smart pointer in the CorrelationId without "
    "allocating memory separately for it. The specified 'smartPtr' "
    "will have its copy constructor invoked when the CorrelationId "
    "is copied and its destructor invoked when the CorrelationId is "
    "destroyed so its resource management will continue to work as "
    "normal. "
    "</para><para> "
    "CorrelationId's based on a simple pointer and CorrelationId's "
    "based on a smart pointer have the same ValueType "
    "(POINTER_VALUE) which allows them to be compared to each other. "
    "</para><para> "
    "A CorrelationId based on a simple pointer and a CorrelationId "
    "based on a smart pointer will compare equally with operator== "
    "as long as the pointer is the same. "
    "</para><para> "
    "Likewise, when comparing two CorrelationId's based on a smart "
    "pointer only the pointer value itself is used for the "
    "comparison, the contents of the smart pointer object are "
    "ignored. "
	)
);
HANDLEX WINAPI
xll_blp_correlation_id(LONG id)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<CorrelationId> cid(new CorrelationId(id));
		h = cid.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddIn xai_blp_correlation_id_value_type(
	Function(XLL_LONG, "?xll_blp_correlation_id_value_type", "BLP.CORRELATION.ID.VALUE.TYPE")
	.Arg(XLL_HANDLE, "CorrelationID", "is a handle returned by BLP.CORRELATION.ID. ")
	.Category(CATEGORY)
	.FunctionHelp("Return the value type associated with CorrelationID.")
	.Documentation(
		"The value types are specified by the <codeInline>BLPAPI_CORRELATION_TYPE_*</codeInline> enumeration. "
	)
);
LONG WINAPI
xll_blp_correlation_id_value_type(HANDLEX cid)
{
#pragma XLLEXPORT
	LONG l(0);

	try {
		handle<CorrelationId> hcid(cid,false);
		ensure (hcid);

		l = hcid->valueType();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return l;
}

static AddIn xai_blp_correlation_id_value(
	Function(XLL_LONG, "?xll_blp_correlation_id_value", "BLP.CORRELATION.ID.VALUE")
	.Arg(XLL_HANDLE, "CorrelationID", "is a handle returned by BLP.CORRELATION.ID. ")
	.Category(CATEGORY)
	.FunctionHelp("Return the value associated with CorrelationID.")
	.Documentation(
		"The CorrelationId must be either an <codeInline>TYPE_AUTOGET</codeInline> or <codeInline>TYPE_INT</codeInline>."
	)
);
LONG WINAPI
xll_blp_correlation_id_value(HANDLEX cid)
{
#pragma XLLEXPORT
	LONG l(0);

	try {
		handle<CorrelationId> hcid(cid,false);
		ensure (hcid);
		ensure (hcid->valueType() == BLPAPI_CORRELATION_TYPE_AUTOGEN || hcid->valueType() == BLPAPI_CORRELATION_TYPE_INT);

		l = static_cast<LONG>(hcid->asInteger());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return l;
}



