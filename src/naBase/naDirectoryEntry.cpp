/**
 * @file        naDirectoryEntry.cpp
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

#include "naDirectoryEntry.h"
#include "naString.h"
#include "naUnicodeUtils.h"

naDirectoryEntry::naDirectoryEntry()
{
#if TARGET_OS_WIN32
    m_hDirent = NULL;
#else
#endif
}

naDirectoryEntry::~naDirectoryEntry()
{
}

bool naDirectoryEntry::Open( const char* utf8Directory )
{
    m_utf8BaseDirectory = utf8Directory;
    m_utf8DirentName = m_utf8BaseDirectory + "\\*";
    return true;
}

bool naDirectoryEntry::Open( const wchar_t* wszDirectory )
{
    return Open( naWSTRINGtoUTF8_s( wszDirectory ).c_str() );
}

bool naDirectoryEntry::OpenF( const char* utf8Format, ... )
{
    va_list vaList;
    std::string strDirectoryName;

    va_start( vaList, utf8Format );
    naStringFormatV( strDirectoryName, utf8Format, vaList );
    va_end( vaList );
    return Open( strDirectoryName.c_str() );
}

bool naDirectoryEntry::OpenF( const wchar_t* wszFormat, ... )
{
    va_list vaList;
    std::wstring wstrDirectoryName;

    va_start( vaList, wszFormat );
    naStringFormatV( wstrDirectoryName, wszFormat, vaList );
    va_end( vaList );
    return Open( wstrDirectoryName.c_str() );
}

bool naDirectoryEntry::FindFiles( const char* utf8FileName )
{
    return true;
}

bool naDirectoryEntry::FindFiles( const wchar_t* wszFileName )
{
    return true;
}

bool naDirectoryEntry::Read( std::string& OUT rstrFilename, size_t* OUT psizeFile, uint32_t* pdwAttributes )
{
#ifdef TARGET_OS_WIN32
    std::wstring wstrFilename;

    if( Read( wstrFilename, psizeFile, pdwAttributes ) == false )
        return false;
    //naWSTRINGtoUTF8( wstrFilename.c_str(), rstrFilename );
    rstrFilename = naWSTRINGtoUTF8_s( wstrFilename.c_str() );
#else
#endif
    return true;
}

bool naDirectoryEntry::Read( std::wstring& OUT rwstrFilename, size_t* OUT psizeFile, uint32_t* OUT pdwAttributes )
{
#ifdef TARGET_OS_WIN32
    WIN32_FIND_DATAW    stFindData;;

    if( naIS_INVALID_HANDLE(m_hDirent) ) {
        std::wstring wstrDirectName = naUTF8toWSTRING_s( m_utf8DirentName.c_str() );
        m_hDirent = ::FindFirstFileW( wstrDirectName.c_str(), &stFindData );
        if( m_hDirent == INVALID_HANDLE_VALUE )
            return false;
    } else {
        if( ::FindNextFileW( m_hDirent, &stFindData ) == FALSE )
            return false;
    }
    rwstrFilename = stFindData.cFileName;
    if( psizeFile )
        *psizeFile = stFindData.nFileSizeLow;
    if( pdwAttributes )
        *pdwAttributes = stFindData.dwFileAttributes;
#else
#endif
    return true;
}

void naDirectoryEntry::Close()
{
}
