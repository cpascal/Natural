/**
 * @file        naMD5.h
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

class naMD5Checksum
{
public:
    naMD5Checksum();
    virtual ~naMD5Checksum();

    void    Reset();
    void    Update( unsigned char* pvData, size_t sizeData );
	void	GetChecksum( uint8_t* pu8Checksum );
	std::string GetChecksumAsString_s();

protected:
	void	Transform( uint32_t* puiBlock );

	typedef	struct	EA_tagMDContext
	{
		uint32_t    au32State[4];		// buf
		uint32_t    au32Count[2];		// number of bits
		uint8_t     abyInput[64];
	} MDCONTEXT, *LPMDCONTEXT;

	MDCONTEXT	m_stContext;
};
