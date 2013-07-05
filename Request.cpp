// Request.cpp - blpapi Request class
// Copyright KALX, LLC. All rights reserved. No warranty made.
#pragma warning(disable: 4244)
#include "blpapi_request.h"
#include "xllblp.h"

using namespace xll;
using namespace BloombergLP;
using namespace blpapi;

static AddInX xai_blp_request_set(
	FunctionX(XLL_HANDLE, "?xll_blp_request_set", "BLP.REQUEST.SET")
	.Arg(XLL_HANDLE, "Request", "is a handle to a Request.")
	.Arg(XLL_CSTRING, "Name", "is the Name being set.")
	.Arg(XLL_LPOPER, "Value", "is that Value associated with Name. ")
	.Category(CATEGORY)
	.FunctionHelp(_T("Description."))
#ifdef _DEBUG
	.Documentation(_T("Documentation."))
#endif
	);
HANDLEX WINAPI
xll_blp_request_set(HANDLEX request, const char* name, LPOPER poValue)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Request> hrequest(request);
		ensure (hrequest);

		const OPER& o = *poValue;
		switch (o.xltype) {
		case xltypeNum:
			{
// uncommenting this breaks delay loading blpapi3_32.dll
//				handle<Datetime> d(o.val.num);
//				if (d)
//					hrequest->set(name, *d);
//				else
					hrequest->set(name, o.val.num);
			}
			break;
		case xltypeStr:
			hrequest->set(name, std::string(o.val.str + 1, o.val.str + o.val.str[0] + 1).c_str());
			break;
		case xltypeBool:
			hrequest->set(name, o.val.xbool != 0);
			break;
		}

		h = request;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_blp_request_append(
	FunctionX(XLL_HANDLE, "?xll_blp_request_append", "BLP.REQUEST.APPEND")
	.Arg(XLL_HANDLE, "Request", "is a handle to a Request.")
	.Arg(XLL_CSTRING, "Name", "is the Name to append.")
	.Arg(XLL_LPOPER, "Value", "is the Value associated with Name. ")
	.Category(CATEGORY)
	.FunctionHelp(_T("Description."))
#ifdef _DEBUG
	.Documentation(_T("Documentation."))
#endif
	);
HANDLEX WINAPI
xll_blp_request_append(HANDLEX request, const char* name, LPOPER poValue)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Request> hrequest(request);
		ensure (hrequest);

		const OPER& o = *poValue;
		switch (o.xltype) {
		case xltypeNum:
			{
// uncommenting this breaks delay loading blpapi3_32.dll
//				handle<Datetime> d(o.val.num);
//				if (d)
//					hrequest->append(name, *d);
//				else
					hrequest->append(name, o.val.num);
			}
			break;
		case xltypeStr:
			hrequest->append(name, std::string(o.val.str + 1, o.val.str + o.val.str[0] + 1).c_str());
			break;
		case xltypeBool:
			hrequest->append(name, o.val.xbool != 0);
			break;
		}

		h = request;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
