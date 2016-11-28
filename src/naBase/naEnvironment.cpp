/**
 * @file        naEnvironment.cpp
 * @author      Standil (cpascal@cpascal.net)
 * @copyright   Copyright (c) 2010-2015 Standil (cpascal@cpascal.net).
 *
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "naEnvironment.h"
#include "naUnicodeUtils.h"
#include <stdlib.h>

std::string naGetEnv( const char* name )
{
	return getenv(name);
}

std::wstring naGetEnv( const wchar_t* name )
{
#if TARGET_OS_WIN32
	return _wgetenv(name);
#else
	std::string utf8Name = naWSTRINGtoUTF8_s(name);
	const char* szValue = getenv(utf8Name.c_str());
	return naUTF8toWSTRING_s(szValue);
#endif
}

int naSetEnv( const char* name, const char* value, int overwrite )
{
#if TARGET_OS_WIN32
    int errcode = 0;
    if(!overwrite) {
        size_t envsize = 0;
        errcode = getenv_s(&envsize, NULL, 0, name);
        if(errcode || envsize) return errcode;
    }
    return _putenv_s(name, value);
#else
	return setenv(name, value, overwrite);
#endif
}

int naSetEnv( const wchar_t* name, const wchar_t* value, int overwrite )
{
#if TARGET_OS_WIN32
    int errcode = 0;
    if(!overwrite) {
        size_t envsize = 0;
        errcode = _wgetenv_s(&envsize, NULL, 0, name);
        if(errcode || envsize) return errcode;
    }
    return _wputenv_s(name, value);
#else
	std::wstring wstrName = naUTF8toWSTRING(name);
	std::wstring wstrValue = naUTF8toWSTRING(value);
	return setenv(wstrName.c_str(), wstrValue.c_str(), overwrite);
#endif
}

int naUnsetEnv( const char* name )
{
#if TARGET_OS_WIN32
	return _putenv_s(name, "");
#else
	return unsetenv(name);
#endif
}

int naUnsetEnv( const wchar_t* name )
{
#if TARGET_OS_WIN32
	return _wputenv_s(name, L"");
#else
	return unsetenv(name);
#endif
}

