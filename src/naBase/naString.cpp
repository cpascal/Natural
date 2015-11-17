/**
 * @file        naString.cpp
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

#include "naString.h"

bool naStringFormatV( std::string& rstrOutput, const char* format, va_list ap)
{
    char szLocalBuffer[256];
    va_list vaClone;

    va_copy(vaClone, ap);
    int nOutputSize = vsnprintf(szLocalBuffer, sizeof(szLocalBuffer)/sizeof(szLocalBuffer[0]), format, vaClone);
    va_end(vaClone);
    if( nOutputSize < 0 )
        return false;
    if( nOutputSize < (sizeof(szLocalBuffer)/sizeof(szLocalBuffer[0]))) {
        rstrOutput.assign( szLocalBuffer, nOutputSize );
        return true;
    }

    char* szDynamicBuffer = new char[nOutputSize+1];
    va_copy(vaClone, ap);
    nOutputSize = vsnprintf(szDynamicBuffer, nOutputSize+1, format, vaClone);
    va_end(vaClone);
    if( nOutputSize < 0 ) {
        delete[] szDynamicBuffer;
        return false;
    }
    rstrOutput.append( szDynamicBuffer, nOutputSize );
    delete[] szDynamicBuffer;
    return true;
}

bool naStringFormatV( std::wstring& rstrOutput, const wchar_t* format, va_list ap)
{
    wchar_t wszLocalBuffer[256];
    va_list vaClone;

    va_copy(vaClone, ap);
    int nOutputSize = _vsnwprintf(wszLocalBuffer, sizeof(wszLocalBuffer)/sizeof(wszLocalBuffer[0]), format, vaClone);
    va_end(vaClone);
    if( nOutputSize < 0 )
        return false;
    if( nOutputSize < (sizeof(wszLocalBuffer)/sizeof(wszLocalBuffer[0]))) {
        rstrOutput.assign( wszLocalBuffer, nOutputSize );
        return true;
    }

    wchar_t* szDynamicBuffer = new wchar_t[nOutputSize+1];
    va_copy(vaClone, ap);
    nOutputSize = _vsnwprintf(szDynamicBuffer, nOutputSize+1, format, vaClone);
    va_end(vaClone);
    if( nOutputSize < 0 ) {
        delete[] szDynamicBuffer;
        return false;
    }
    rstrOutput.append( szDynamicBuffer, nOutputSize );
    delete[] szDynamicBuffer;
    return true;
}

