// Datetime.cpp - blpapi Datetime class
// Copyright KALX, LLC. All rights reserved. No warranty made.
#pragma warning(disable: 4244)
#include "blpapi_datetime.h"
#include "xllblp.h"

using namespace xll;
using namespace BloombergLP;
using namespace blpapi;

BloombergLP::blpapi::Datetime xll::to_datetime(const OPER& d)
{
	return BloombergLP::blpapi::Datetime(
		static_cast<int>(XLL_XLF(Year, d)), 
		static_cast<int>(XLL_XLF(Month, d)), 
		static_cast<int>(XLL_XLF(Day, d)), 
		static_cast<int>(XLL_XLF(Hour, d)), 
		static_cast<int>(XLL_XLF(Minute, d)), 
		static_cast<int>(XLL_XLF(Second, d))
	);
}
OPER xll::from_datetime(const BloombergLP::blpapi::Datetime& d)
{
	return OPER(XLL_XLF(Date, OPER(d.year()), OPER(d.month()), OPER(d.day()))
			    + XLL_XLF(Time, OPER(d.hours()), OPER(d.minutes()), OPER(d.seconds())));
}


static AddIn xai_blp_datetime_set(
	Function(XLL_HANDLE, "?xll_blp_datetime_set", "BLP.DATETIME.SET")
	.Arg(XLL_DOUBLE, "Date", "is an Excel Julian Date. ")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Convert from Excel to Open Bloomberg datetime.")
#ifdef _DEBUG
	.Documentation("Rounds to the nearest second." )
#endif
	);
HANDLEX WINAPI
xll_blp_datetime_set(double date)
{
#pragma XLLEXPORT
	HANDLEX h(0);

	try {
		handle<Datetime> hdate(new Datetime(to_datetime(OPER(date))));

		h = hdate.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddIn xai_blp_datetime_get(
	Function(XLL_DOUBLE, "?xll_blp_datetime_get", "BLP.DATETIME.GET")
	.Arg(XLL_HANDLE, "Date", "is a handle to an Open Bloomberg Datetime. ")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Convert from Open Bloomberg to Excel to datetime.")
#ifdef _DEBUG
	.Documentation("Rounds to the nearest second. ")
#endif
	);
double WINAPI
xll_blp_datetime_get(HANDLEX date)
{
#pragma XLLEXPORT
	double d(0);

	try {
		handle<Datetime> hdate(date,false);

		d = from_datetime(*hdate);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return d;
}
