// Name.cpp - blpapi Name class
// Copyright KALX, LLC. All rights reserved. No warranty made.
#pragma warning(disable: 4244)
#include "blpapi_name.h"
#include "xllblp.h"

using namespace xll;
using namespace BloombergLP;
using namespace blpapi;


static AddInX xai_blp_name(
	FunctionX(XLL_HANDLE, "?xll_blp_name", "BLP.NAME")
	.Arg(XLL_CSTRING, "Name", "is a string.")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to a blpapi Name object.")
#ifdef _DEBUG
	.Documentation(
		"Documentation."
	)
#endif
	);
HANDLEX WINAPI
xll_blp_name(const char* name)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Name> hname(new Name(name));

		h = hname.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_blp_name_string(
	FunctionX(XLL_CSTRING, "?xll_blp_name_string", "BLP.NAME.STRING")
	.Arg(XLL_HANDLE, "Name", "is handle to a Name object.")
	.Category(CATEGORY)
	.FunctionHelp("Return the string name corresponding the the handle.")
#ifdef _DEBUG
	.Documentation(
		"Documentation."
	)
#endif
	);
const char* WINAPI
xll_blp_name_string(HANDLEX name)
{
#pragma XLLEXPORT
	const char* s(0);

	try {
		handle<Name> hname(name,false);
		ensure (hname);

		s = hname->string();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s;
}
