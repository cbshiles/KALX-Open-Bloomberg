// xllblp.cpp - blpapi Excel wrappers
// Copyright KALX, LLC. All rights reserved. No warranty made.
#include "xllblp.h"

using namespace xll;

#ifdef _DEBUG
static AddIn xai_blp(
	Document(CATEGORY)
	.Documentation("Excel add-ins for the Open Bloomberg API library. ")
);
#endif // _DEBUG

// Add dll directory to PATH variable for delay loading blpapi3_32.dll
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
int xll_add_path(void)
{
	try {
		xchar base[_MAX_PATH];
		xchar path[0xFFFF];

		DWORD nbase = GetModuleFileName((HINSTANCE)&__ImageBase, base, _MAX_PATH);
		DWORD npath = GetEnvironmentVariable(_T("PATH"), path, 0xFFFF);
		ensure(npath + nbase < 0xFFFF);

		_tcscat (path, ";");
		_tcscat (path, Directory::Basename(base).c_str());

		ensure (SetEnvironmentVariable(_T("PATH"), path));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<Open> xao_add_path(xll_add_path);