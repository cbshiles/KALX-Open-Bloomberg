// Service.cpp - blpapi Service object
// Copyright KALX, LLC. All rights reserved. No warranty made.
#pragma warning(disable: 4244)
#include "blpapi_service.h"
#include "xllblp.h"

using namespace xll;
using namespace BloombergLP;
using namespace blpapi;

static AddIn xai_blp_service_num_operations(
	Function(XLL_LONG, "?xll_blp_service_num_operations", "BLP.SERVICE.NUM.OPERATIONS")
	.Arg(XLL_HANDLE, "Service", "is a handle returned by BLP.SESSION.GET.SERVICE.")
	.Category(CATEGORY)
	.FunctionHelp("Return the number of Operations defined by the Service.")
	.Documentation(
		"Use the functions below to get more information."
		,
		xml::xlink("BLP.SERVICE.OPERATION.NAME")
	)
);
LONG WINAPI
xll_blp_service_num_operations(HANDLEX service)
{
#pragma XLLEXPORT
	LONG n(0);

	try {
		handle<Service> hs(service,false);
		ensure (hs && hs->isValid());

		n = hs->numOperations();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return n;
}

static AddIn xai_blp_service_operation_name(
	Function(XLL_CSTRING, "?xll_blp_service_operation_name", "BLP.SERVICE.OPERATION.NAME")
	.Arg(XLL_HANDLE, "Service", "is a handle returned by BLP.SESSION.GET.SERVICE.")
	.Arg(XLL_USHORT, "Index", "is the Index of the Operation in Service. ")
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the name of the Operation."))
);
const char* WINAPI
xll_blp_service_operation_name(HANDLEX service, USHORT index)
{
#pragma XLLEXPORT
	const char* s(0);

	try {
		handle<Service> hs(service,false);
		ensure (hs && hs->isValid());
		ensure (index < hs->numOperations());

		s = hs->getOperation(index).name();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return s;
}

static AddIn xai_blp_service_operation_description(
	Function(XLL_CSTRING, "?xll_blp_service_operation_description", "BLP.SERVICE.OPERATION.DESCRIPTION")
	.Arg(XLL_HANDLE, "Service", "is a handle returned by BLP.SESSION.GET.SERVICE.")
	.Arg(XLL_USHORT, "Index", "is the Index of the Operation in Service. ")
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the description of the Operation."))
);
const char* WINAPI
xll_blp_service_operation_description(HANDLEX service, USHORT index)
{
#pragma XLLEXPORT
	const char* s(0);

	try {
		handle<Service> hs(service,false);
		ensure (hs && hs->isValid());
		ensure (index < hs->numOperations());

		s = hs->getOperation(index).description();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return s;
}

static AddIn xai_blp_service_create_request(
	Function(XLL_HANDLE, "?xll_blp_service_create_request", "BLP.SERVICE.CREATE.REQUEST")
	.Arg(XLL_HANDLE, "Service", "is a handle returned by BLP.SESSION.GET.SERVICE.")
	.Arg(XLL_CSTRING, "Operation", "is the Operation being requested. ")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to an empty Request object.")
	.Documentation(
        "Returns a empty Request object for the specified "
        "'operation'. If 'operation' does not identify a valid "
        "operation in the Service then an exception is thrown. "
		"</para><para>"
        "An application must populate the Request before issuing it "
		"using <codeInline>BLP.SESSION.SEND.REQUEST()</codeInline>. "
	)
);
HANDLEX WINAPI
xll_blp_service_create_request(HANDLEX service, const char* operation)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Service> hs(service,false);
		ensure (hs && hs->isValid());

		Request req = hs->createRequest(operation);

		h = p2h<Request>(&req);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return h;
}

