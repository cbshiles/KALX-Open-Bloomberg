// xllblp.h - Open Bloomberg Excel add-in
// Uncomment the following line to use features for Excel2007 and above.
// #define EXCEL12
#include "xll/xll.h"

#ifndef CATEGORY
#define CATEGORY "BLP"
#endif

typedef xll::traits<XLOPERX>::xchar xchar;
typedef xll::traits<XLOPERX>::xcstr xcstr;
typedef xll::traits<XLOPERX>::xstring xstring;
typedef xll::traits<XLOPERX>::xword xword;

namespace BloombergLP { namespace blpapi { class Datetime; } }

namespace xll {

	extern BloombergLP::blpapi::Datetime to_datetime(const OPER&);
	extern OPER from_datetime(const BloombergLP::blpapi::Datetime&);

} // namespace xll


