// Element.cpp - blpapi Element class
// Copyright KALX, LLC. All rights reserved. No warranty made.
#pragma warning(disable: 4244)
#include "blpapi_element.h"
#include "xllblp.h"

using namespace xll;
using namespace BloombergLP;
using namespace blpapi;

// scalar elements
inline void setValue(Element& e, const OPER& value)
{
	switch (value.xltype) {
	case xltypeNum:
		e.setValue(value.val.num); // check if date???
		break;
	case xltypeStr:
		e.setValue(to_string<XLOPER>(value).c_str());
		break;
	case xltypeBool:
		e.setValue(value.val.xbool != 0);
		break;
	case xltypeInt: // never happens
		e.setValue(value.val.w);
		break;
	case xltypeMulti: 
		{
		}
		break;
	}
}
// scalar elements
inline OPER getValue(Element& e)
{
	switch (e.datatype()) {
	case BLPAPI_DATATYPE_DATE:
	case BLPAPI_DATATYPE_TIME:
	case BLPAPI_DATATYPE_DATETIME:
		return from_datetime(e.getValueAsDatetime());

	case BLPAPI_DATATYPE_FLOAT64:
		return OPER(e.getValueAsFloat64());

	case BLPAPI_DATATYPE_FLOAT32:
		return OPER(e.getValueAsFloat32());

	case BLPAPI_DATATYPE_INT32:
		return OPER(e.getValueAsInt32());

	case BLPAPI_DATATYPE_INT64:
		return OPER(static_cast<double>(e.getValueAsInt64()));

	case BLPAPI_DATATYPE_CHAR:
	case BLPAPI_DATATYPE_STRING:
		return OPER(e.getValueAsString());

	case BLPAPI_DATATYPE_BOOL:
		return OPER(e.getValueAsBool());

	default:
		XLL_ERROR("getValue: unrecognized datatype");
	}

	return Err(xlerrNA);
}

static AddIn xai_blp_element(
	Function(XLL_HANDLE, "?xll_blp_element", "BLP.ELEMENT")
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
xll_blp_element(LPOPER pxValue)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Element> e(new Element());
		setValue(*e, *pxValue); //??? fails

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

//
// Accessors
//

static AddIn xai_blp_element_name(
	Function(XLL_CSTRING, "?xll_blp_element_name", "BLP.ELEMENT.NAME")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element.")
	.Category(CATEGORY)
	.FunctionHelp("Return the name of an Element.")
	.Documentation(
        "If this Element is part of a sequence or choice Element then return "
        "the Name of this Element within the sequence or choice Element that "
        "owns it. If this Element is not part of a sequence Element (that is "
        "it is an entire Request or Message) then return the Name of the "
        "Request or Message. "
	)
);
const char* WINAPI
xll_blp_element_name(HANDLEX element)
{
#pragma XLLEXPORT
	static const char* name("");

	try {
		handle<Element> he(element,false);
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

XLL_ENUM_DOC(BLPAPI_DATATYPE_BOOL, BLPAPI_DATATYPE_BOOL, CATEGORY, "Bool", "Value is 1")
XLL_ENUM_DOC(BLPAPI_DATATYPE_CHAR, BLPAPI_DATATYPE_CHAR, CATEGORY, "Char", "Value is 2")
XLL_ENUM_DOC(BLPAPI_DATATYPE_BYTE, BLPAPI_DATATYPE_BYTE, CATEGORY, "Unsigned 8 bit value", "Value is 3")
XLL_ENUM_DOC(BLPAPI_DATATYPE_INT32, BLPAPI_DATATYPE_INT32, CATEGORY, "32 bit Integer", "Value is 4")
XLL_ENUM_DOC(BLPAPI_DATATYPE_INT64, BLPAPI_DATATYPE_INT64, CATEGORY, "64 bit Integer", "Value is 5")
XLL_ENUM_DOC(BLPAPI_DATATYPE_FLOAT32, BLPAPI_DATATYPE_FLOAT32, CATEGORY, "32 bit Floating point - IEEE", "Value is 6")
XLL_ENUM_DOC(BLPAPI_DATATYPE_FLOAT64, BLPAPI_DATATYPE_FLOAT64, CATEGORY, "64 bit Floating point - IEEE", "Value is 7")
XLL_ENUM_DOC(BLPAPI_DATATYPE_STRING, BLPAPI_DATATYPE_STRING, CATEGORY, "ASCIIZ string", "Value is 8")
XLL_ENUM_DOC(BLPAPI_DATATYPE_BYTEARRAY, BLPAPI_DATATYPE_BYTEARRAY, CATEGORY, "Opaque binary data", "Value is 9")
XLL_ENUM_DOC(BLPAPI_DATATYPE_DATE, BLPAPI_DATATYPE_DATE, CATEGORY, "Date", "Value is 10")
XLL_ENUM_DOC(BLPAPI_DATATYPE_TIME, BLPAPI_DATATYPE_TIME, CATEGORY, "Timestamp", "Value is 11")
XLL_ENUM_DOC(BLPAPI_DATATYPE_DECIMAL, BLPAPI_DATATYPE_DECIMAL, CATEGORY, "", "Value is 12")
XLL_ENUM_DOC(BLPAPI_DATATYPE_DATETIME, BLPAPI_DATATYPE_DATETIME, CATEGORY, "Date and time", "Value is 13")
XLL_ENUM_DOC(BLPAPI_DATATYPE_ENUMERATION, BLPAPI_DATATYPE_ENUMERATION, CATEGORY, "An opaque enumeration", "Value is 14")
XLL_ENUM_DOC(BLPAPI_DATATYPE_SEQUENCE, BLPAPI_DATATYPE_SEQUENCE, CATEGORY, "Sequence type", "Value is 15")
XLL_ENUM_DOC(BLPAPI_DATATYPE_CHOICE, BLPAPI_DATATYPE_CHOICE, CATEGORY, "Choice type", "Value is 16")
XLL_ENUM_DOC(BLPAPI_DATATYPE_CORRELATION_ID, BLPAPI_DATATYPE_CORRELATION_ID, CATEGORY, "Used for some internal messages", "Value is 17")

static AddIn xai_blp_element_datatype(
	Function(XLL_LONG, "?xll_blp_element_datatype", "BLP.ELEMENT.DATATYPE")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element.")
	.Category(CATEGORY)
	.FunctionHelp("Return the datatype of an Element from the BLPAPI_DATATYPE_* enumeration.")
	.Documentation(
		"Return the basic data type used to represent a value in this "
        "element. The possible return values are enumerated in "
		"the <codeInline>BLPAPI_DATATYPE_*</codeInline> enumeration. "
	)
);
LONG WINAPI
xll_blp_element_datatype(HANDLEX element)
{
#pragma XLLEXPORT
	LONG l(0);

	try {
		handle<Element> he(element,false);
		ensure (he && he->isValid());

		l = he->datatype();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return l;
}

static AddIn xai_blp_is_complex_type(
	Function(XLL_BOOL, "?xll_blp_is_complex_type", "BLP.ELEMENT.IS.COMPLEX.TYPE")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element.")
	.Category(CATEGORY)
	.FunctionHelp("Return true for complex Element types.")
	.Documentation(
		"Return true if the datatype is a <codeInline>BLPAPI_DATATYPE_SEQUENCE</codeInline> or "
        "<codeInline>BLPAPI_DATATYPE_CHOICE</codeInline> and false otherwise. "
	)
);
BOOL WINAPI
xll_blp_is_complex_type(HANDLEX element)
{
#pragma XLLEXPORT
	BOOL b(false);

	try {
		handle<Element> he(element,false);
		ensure (he && he->isValid());

		b = he->isComplexType();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return b;
}

static AddIn xai_blp_is_array(
	Function(XLL_BOOL, "?xll_blp_is_array", "BLP.ELEMENT.IS.ARRAY")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element. ")
	.Category(CATEGORY)
	.FunctionHelp("Return true for nonscalar Elements.")
	.Documentation(
		"Return true if 'elementDefinition().maxValues() > 1' or "
        "'elementDefinition().maxValues() == UNBOUNDED', and false otherwise. "
	)
);
BOOL WINAPI
xll_blp_is_array(HANDLEX element)
{
#pragma XLLEXPORT
	bool b(false);

	try {
		handle<Element> he(element,false);
		ensure (he && he->isValid());

		b = he->isArray();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return b;
}

static AddIn xai_blp_is_null(
	Function(XLL_BOOL, "?xll_blp_is_null", "BLP.ELEMENT.IS.NULL")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element. ")
	.Category(CATEGORY)
	.FunctionHelp("Return true if this element has a null value, and false otherwise.")
	.Documentation(
		 ""
	)
);
BOOL WINAPI
xll_blp_is_null(HANDLEX element)
{
#pragma XLLEXPORT
	BOOL b(false);

	try {
		handle<Element> he(element,false);
		ensure (he && he->isValid());

		b = he->isNull();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return b;
}

static AddIn xai_blp_is_read_only(
	Function(XLL_BOOL, "?xll_blp_is_read_only", "BLP.ELEMENT.IS.READ.ONLY")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element. ")
	.Category(CATEGORY)
	.FunctionHelp("Return true if this element cannot be modified, and false otherwise.")
	.Documentation(
		 ""
	)
);
BOOL WINAPI
xll_blp_is_read_only(HANDLEX element)
{
#pragma XLLEXPORT
	BOOL b(false);

	try {
		handle<Element> he(element,false);
		ensure (he && he->isValid());

		b = he->isNull();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return b;
}

static AddIn xai_blp_num_values(
	Function(XLL_LONG, "?xll_blp_num_values", "BLP.ELEMENT.NUM.VALUES")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element. ")
	.Category(CATEGORY)
	.FunctionHelp("Return true if this element cannot be modified, and false otherwise.")
	.Documentation(
        "Return the number of values contained by this element. The number of "
        "values is 0 if 'isNull()' returns true, and no greater than 1 if "
        "'isComplexType()' returns true. The value returned will always be in "
        "the range defined by 'elementDefinition().minValues()' and "
        "'elementDefinition().maxValues()'. "
	)
);
LONG WINAPI
xll_blp_num_values(HANDLEX element)
{
#pragma XLLEXPORT
	LONG l(0);

	try {
		handle<Element> he(element,false);
		ensure (he && he->isValid());

		l = he->numValues();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return l;
}

static AddIn xai_blp_num_elements(
	Function(XLL_LONG, "?xll_blp_num_elements", "BLP.ELEMENT.NUM.ELEMENTS")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element. ")
	.Category(CATEGORY)
	.FunctionHelp("Return true if this element cannot be modified, and false otherwise.")
	.Documentation(
        "Return the number of elements contained by this element.  The number "
        "of elements is 0 if 'isComplex()' returns false, and no greater than "
        "1 if the Datatype is CHOICE; if the DataType is SEQUENCE this may "
        "return any number (including 0). "
	)
);
LONG WINAPI
xll_blp_num_elements(HANDLEX element)
{
#pragma XLLEXPORT
	LONG l(0);

	try {
		handle<Element> he(element,false);
		ensure (he && he->isValid());

		l = he->numValues();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return l;
}

static AddIn xai_blp_is_valid(
	Function(XLL_BOOL, "?xll_blp_is_valid", "BLP.ELEMENT.IS.READ.ONLY")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element. ")
	.Category(CATEGORY)
	.FunctionHelp("Return true if this element is valid.")
	.Documentation(
		"An Element created using the default constructor is not valid until it has had a value assigned to it. "
	)
);
BOOL WINAPI
xll_blp_is_valid(HANDLEX element)
{
#pragma XLLEXPORT
	BOOL b(false);

	try {
		handle<Element> he(element,false);

		b = he->isValid();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return b;
}

static AddIn xai_blp_is_null_value(
	Function(XLL_BOOL, "?xll_blp_is_null_value", "BLP.ELEMENT.IS.NULL.VALUE")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element.")
	.Arg(XLL_USHORT, "Index", "is the position of the sub element. ")
	.Category(CATEGORY)
	.FunctionHelp("Return true if sub Element at Index is null.")
	.Documentation(
		""
	)
);
BOOL WINAPI
xll_blp_is_null_value(HANDLEX element, USHORT i)
{
#pragma XLLEXPORT
	BOOL b(false);

	try {
		handle<Element> he(element,false);
		ensure (he && he->isValid());

		b = he->isNullValue(i);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return b;
}

static AddIn xai_blp_element_get_value(
	Function(XLL_LPOPER, "?xll_blp_element_get_value", "BLP.ELEMENT.GET.VALUE")
	.Arg(XLL_HANDLE, "Element", "is a handle to an Element.")
	.Arg(XLL_USHORT, "Index", "is an optional Index when Element is an array. ")
	.Category(CATEGORY)
	.FunctionHelp("Get Element value at Index.")
	.Documentation(
	)
);
LPOPER WINAPI
xll_blp_element_get_value(HANDLEX element, USHORT i)
{
#pragma XLLEXPORT
	static OPER o;

	try {
		handle<Element> he(element,false);
		ensure (he && he->isValid());

		Element e = he->getValueAsElement(i);
		o = getValue(e);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());
	}

	return &o;
}

#ifdef _DEBUG

int xll_test_element(void)
{
	try {
		Element e;
//		e.appendValue(true);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}
	catch (const Exception& ex) {
		XLL_ERROR(ex.description().c_str());

		return 0;
	}

	return 1;
}
static Auto<Open> xao_test_element(xll_test_element);

#endif // _DEBUG