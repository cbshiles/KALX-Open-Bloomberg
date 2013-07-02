// Element.cpp - blpapi Element class
#pragma warning(disable: 4244)
#include "blpapi_element.h"
#include "xllblp.h"

using namespace xll;
using namespace BloombergLP;
using namespace blpapi;

// scalar elements
inline void setElement(Element& e, const char* name, const OPER& value)
{
	switch (value.xltype) {
	case xltypeNum:
		e.setElement(name, value.val.num); // check if date???
		break;
	case xltypeStr:
		e.setElement(name, to_string<XLOPER>(value).c_str());
		break;
	case xltypeBool:
		e.setElement(name, value.val.xbool != 0);
		break;
	case xltypeInt: // never happens
		e.setElement(name, value.val.w);
		break;
	case xltypeMulti: 
		{
		}
		break;
	}
}

static AddInX xai_blp_element(
	FunctionX(XLL_HANDLE, _T("?xll_blp_element"), _T("BLP.ELEMENT"))
	.Arg(XLL_CSTRING, "Name", "is the Element Name.")
	.Arg(XLL_LPOPER, "Value", "is the Element Value. ")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return an Element having a Name/Value pair."))
	.Documentation(
		"An Element represents an item in a message. "
		"</para><para>"
		"An Element can represent: a single value of any data type supported by "
		"the Bloomberg API; an array of values; a sequence or a choice. "
	)
);
HANDLEX WINAPI
xll_blp_element(const char* name, LPOPER pxValue)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Element> e(new Element());
		setElement(*e, name, *pxValue);

		h = e.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return h;
}

static AddInX xai_blp_element_name(
	FunctionX(XLL_CSTRING, _T("?xll_blp_element_name"), _T("BLP.ELEMENT.NAME"))
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element.")
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the name of an Element."))
	.Documentation(
	)
);
const char* WINAPI
xll_blp_element_name(HANDLEX element)
{
#pragma XLLEXPORT
	static const char* name("");

	try {
		handle<Element> he(element);
		ensure (he);

		if (he->isValid())
			name = he->name().string();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return name;
}

static AddInX xai_blp_element_datatype(
	FunctionX(XLL_LONG, _T("?xll_blp_element_datatype"), _T("BLP.ELEMENT.DATATYPE"))
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element.")
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the name of an Element."))
	.Documentation(
	)
);
LONG WINAPI
xll_blp_element_datatype(HANDLEX element)
{
#pragma XLLEXPORT
	int datatype;

	try {
		handle<Element> he(element);
		ensure (he);

		if (he->isValid())
			datatype = he->datatype();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return datatype;
}