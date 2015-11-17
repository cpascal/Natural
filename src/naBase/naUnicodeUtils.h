/**
 * @file        naUnicodeUtils.h
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

#pragma once

#include "naPlatformDefine.h"

size_t naUTF16toUTF8( const char16_t* utf16InString, char* utf8OutString, size_t IN sizeCount );
size_t naUTF8toUTF16( const char* utf8InString, char16_t* utf16OutString, size_t IN sizeCount );
size_t naWSTRINGtoUTF8( const wchar_t* wszSource, char* u8Destination, size_t IN sizeCount );
size_t naUTF8toWSTRING( const char* u8szSource, wchar_t* wszDestination, size_t IN sizeCount );

std::string naUTF16toUTF8_s( const char16_t* u16szInString );
std::u16string naUTF8toUTF16_s( const char* u8szInString );
std::string naWSTRINGtoUTF8_s( const wchar_t* wszString );
std::wstring naUTF8toWSTRING_s( const char* u8szString );

