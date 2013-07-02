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

static AddIn xai_blp_element(
	Function(XLL_HANDLE, "?xll_blp_element", "BLP.ELEMENT")
	.Arg(XLL_CSTRING, "Name", "is the Element Name.")
	.Arg(XLL_LPOPER, "Value", "is the Element Value. ")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return an Element having a Name/Value pair.")
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

static AddIn xai_blp_element_name(
	Function(XLL_CSTRING, "?xll_blp_element_name", "BLP.ELEMENT.NAME")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element.")
	.Category(CATEGORY)
	.FunctionHelp("Return the name of an Element.")
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
		ensure (he && he->isValid());

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

XLL_ENUM_DOC(BLPAPI_DATATYPE_BOOL, BLPAPI_DATATYPE_BOOL, CATEGORY, "Bool", "Has the value 1")
XLL_ENUM_DOC(BLPAPI_DATATYPE_CHAR, BLPAPI_DATATYPE_CHAR, CATEGORY, "Char", "Has the value 2")
XLL_ENUM_DOC(BLPAPI_DATATYPE_BYTE, BLPAPI_DATATYPE_BYTE, CATEGORY, "Unsigned 8 bit value", "Has the value 3")
XLL_ENUM_DOC(BLPAPI_DATATYPE_INT32, BLPAPI_DATATYPE_INT32, CATEGORY, "32 bit Integer", "Has the value 4")
XLL_ENUM_DOC(BLPAPI_DATATYPE_INT64, BLPAPI_DATATYPE_INT64, CATEGORY, "64 bit Integer", "Has the value 5")
XLL_ENUM_DOC(BLPAPI_DATATYPE_FLOAT32, BLPAPI_DATATYPE_FLOAT32, CATEGORY, "32 bit Floating point - IEEE", "Has the value 6")
XLL_ENUM_DOC(BLPAPI_DATATYPE_FLOAT64, BLPAPI_DATATYPE_FLOAT64, CATEGORY, "64 bit Floating point - IEEE", "Has the value 7")
XLL_ENUM_DOC(BLPAPI_DATATYPE_STRING, BLPAPI_DATATYPE_STRING, CATEGORY, "ASCIIZ string", "Has the value 8")
XLL_ENUM_DOC(BLPAPI_DATATYPE_BYTEARRAY, BLPAPI_DATATYPE_BYTEARRAY, CATEGORY, "Opaque binary data", "Has the value 9")
XLL_ENUM_DOC(BLPAPI_DATATYPE_DATE, BLPAPI_DATATYPE_DATE, CATEGORY, "Date", "Has the value 10")
XLL_ENUM_DOC(BLPAPI_DATATYPE_TIME, BLPAPI_DATATYPE_TIME, CATEGORY, "Timestamp", "Has the value 11")
XLL_ENUM_DOC(BLPAPI_DATATYPE_DECIMAL, BLPAPI_DATATYPE_DECIMAL, CATEGORY, "", "Has the value 12")
XLL_ENUM_DOC(BLPAPI_DATATYPE_DATETIME, BLPAPI_DATATYPE_DATETIME, CATEGORY, "Date and time", "Has the value 13")
XLL_ENUM_DOC(BLPAPI_DATATYPE_ENUMERATION, BLPAPI_DATATYPE_ENUMERATION, CATEGORY, "An opaque enumeration", "Has the value 14")
XLL_ENUM_DOC(BLPAPI_DATATYPE_SEQUENCE, BLPAPI_DATATYPE_SEQUENCE, CATEGORY, "Sequence type", "Has the value 15")
XLL_ENUM_DOC(BLPAPI_DATATYPE_CHOICE, BLPAPI_DATATYPE_CHOICE, CATEGORY, "Choice type", "Has the value 16")
XLL_ENUM_DOC(BLPAPI_DATATYPE_CORRELATION_ID, BLPAPI_DATATYPE_CORRELATION_ID, CATEGORY, "Used for some internal messages", "Has the value 17")

static AddIn xai_blp_element_datatype(
	Function(XLL_LONG, "?xll_blp_element_datatype", "BLP.ELEMENT.DATATYPE")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element.")
	.Category(CATEGORY)
	.FunctionHelp("Return the datatype of an Element from the BLPAPI_DATATYPE_* enumeration.")
	.Documentation(
	)
);
LONG WINAPI
xll_blp_element_datatype(HANDLEX element)
{
#pragma XLLEXPORT
	int datatype(0);

	try {
		handle<Element> he(element);
		ensure (he && he->isValid());

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

static AddIn xai_blp_is_complex_type(
	Function(XLL_LONG, "?xll_blp_is_complex_type", "BLP.ELEMENT.IS.COMPLEX.TYPE")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element.")
	.Category(CATEGORY)
	.FunctionHelp("Return the datatype of an Element from the BLPAPI_DATATYPE_* enumeration.")
	.Documentation(
	)
);
BOOL WINAPI
xll_blp_is_complex_type(HANDLEX element)
{
#pragma XLLEXPORT
	bool type(false);

	try {
		handle<Element> he(element);
		ensure (he && he->isValid());

		type = he->isComplexType();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return type;
}