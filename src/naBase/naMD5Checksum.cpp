#include "naMD5Checksum.h"

#define	EA_TO_LITTLEENDIAN_32BIT( nValue )	nValue
#define	EA_TO_LITTLEENDIANS_32BIT( pOut, pIn, sizeCount )	memcpy( pOut, pIn, sizeCount * sizeof( uint32_t ) )

#define	MD5_F( x, y, z )	( ( (x) & (y) ) | ( (~x) & (z) ) )
#define	MD5_G( x, y, z )	( ( (x) & (z) ) | ( (y) & (~z) ) )
#define	MD5_H( x, y, z )	( (x) ^ (y) ^ (z) )
#define	MD5_I( x, y, z )	( (y) ^ ( (x) | (~z) ) )

#define	ROTATE_LEFT( x, n )	( ( (x) << (n) ) | ( (x) >> ( 32 - (n) ) ) )

#define	MD5_FF( a, b, c, d, x, s, ac ) {					\
    (a)	+= MD5_F( (b), (c), (d) ) + (x) + (uint32_t)(ac);		\
    (a)	= ROTATE_LEFT( (a), (s) );				\
    (a)	+= (b);							\
    }

#define	MD5_GG( a, b, c, d, x, s, ac ) {					\
    (a)	+= MD5_G( (b), (c), (d) ) + (x) + (uint32_t)(ac);		\
    (a)	= ROTATE_LEFT( (a), (s) );				\
    (a)	+= (b);							\
    }

#define	MD5_HH( a, b, c, d, x, s, ac ) {					\
    (a)	+= MD5_H( (b), (c), (d) ) + (x) + (uint32_t)(ac);		\
    (a)	= ROTATE_LEFT( (a), (s) );				\
    (a)	+= (b);							\
    }

#define	MD5_II( a, b, c, d, x, s, ac ) {					\
    (a)	+= MD5_I( (b),(c), (d) ) + (x) + (uint32_t)(ac);		\
    (a)	= ROTATE_LEFT( (a), (s) );				\
    (a)	+= (b);							\
    }

#define MD5_S11 7  /* Round 1 */
#define MD5_S12 12
#define MD5_S13 17
#define MD5_S14 22
#define MD5_S21 5  /* Round 2 */
#define MD5_S22 9
#define MD5_S23 14
#define MD5_S24 20
#define MD5_S31 4  /* Round 3 */
#define MD5_S32 11
#define MD5_S33 16
#define MD5_S34 23
#define MD5_S41 6  /* Round 4 */
#define MD5_S42 10
#define MD5_S43 15
#define MD5_S44 21

const	uint32_t g_u32MDInitializeTable[4] = {
	0x67452301UL,
	0xEFCDAB89UL,
	0x98BADCFEUL,
	0x10325476UL
};

const	uint8_t g_u8MDPaddingTable[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

naMD5Checksum::naMD5Checksum()
{
    Reset();
}

naMD5Checksum::~naMD5Checksum()
{
}

void naMD5Checksum::Reset()
{
    m_stContext.au32Count[0]	= m_stContext.au32Count[1]	= 0;

    m_stContext.au32State[0]	= g_u32MDInitializeTable[0];
    m_stContext.au32State[1]	= g_u32MDInitializeTable[1];
    m_stContext.au32State[2]	= g_u32MDInitializeTable[2];
    m_stContext.au32State[3]	= g_u32MDInitializeTable[3];
}

void	naMD5Checksum::Update( unsigned char* pvData, uint32_t u32DataLen )
{
    LPBYTE	pbyData	= (LPBYTE)pvData;
    uint32_t	u32Input[16];
    uint32_t	u32Index = 0;

    u32Index	= (uint32_t)( ( m_stContext.au32Count[0] >> 3 ) & 0x3F );
    if( ( m_stContext.au32Count[0] + (uint32_t)( u32DataLen << 3 ) ) < m_stContext.au32Count[0] )
        m_stContext.au32Count[1]++;

    m_stContext.au32Count[0] += (uint32_t)( u32DataLen << 3 );
    m_stContext.au32Count[1] += (uint32_t)( u32DataLen >> 29 );

    while( u32DataLen-- ) {
        m_stContext.abyInput[ u32Index++ ]	= *pbyData++;

        if( u32Index == 0x40 ) { //64 
            EA_TO_LITTLEENDIANS_32BIT( u32Input, (uint32_t *) m_stContext.abyInput, 16 );

            Transform( u32Input );
            u32Index	= 0;
        }
    }
}

void	naMD5Checksum::Transform( uint32_t *pu32Block )
{
    uint32_t a, b, c, d;
    uint32_t* pu32State  = m_stContext.au32State;
    a				= pu32State[0];
    b				= pu32State[1];
    c				= pu32State[2];
    d				= pu32State[3];

    MD5_FF ( a, b, c, d, pu32Block[ 0], MD5_S11, (uint32_t) 3614090360u); /* 1 */
    MD5_FF ( d, a, b, c, pu32Block[ 1], MD5_S12, (uint32_t) 3905402710u); /* 2 */
    MD5_FF ( c, d, a, b, pu32Block[ 2], MD5_S13, (uint32_t)  606105819u); /* 3 */
    MD5_FF ( b, c, d, a, pu32Block[ 3], MD5_S14, (uint32_t) 3250441966u); /* 4 */
    MD5_FF ( a, b, c, d, pu32Block[ 4], MD5_S11, (uint32_t) 4118548399u); /* 5 */
    MD5_FF ( d, a, b, c, pu32Block[ 5], MD5_S12, (uint32_t) 1200080426u); /* 6 */
    MD5_FF ( c, d, a, b, pu32Block[ 6], MD5_S13, (uint32_t) 2821735955u); /* 7 */
    MD5_FF ( b, c, d, a, pu32Block[ 7], MD5_S14, (uint32_t) 4249261313u); /* 8 */
    MD5_FF ( a, b, c, d, pu32Block[ 8], MD5_S11, (uint32_t) 1770035416u); /* 9 */
    MD5_FF ( d, a, b, c, pu32Block[ 9], MD5_S12, (uint32_t) 2336552879u); /* 10 */
    MD5_FF ( c, d, a, b, pu32Block[10], MD5_S13, (uint32_t) 4294925233u); /* 11 */
    MD5_FF ( b, c, d, a, pu32Block[11], MD5_S14, (uint32_t) 2304563134u); /* 12 */
    MD5_FF ( a, b, c, d, pu32Block[12], MD5_S11, (uint32_t) 1804603682u); /* 13 */
    MD5_FF ( d, a, b, c, pu32Block[13], MD5_S12, (uint32_t) 4254626195u); /* 14 */
    MD5_FF ( c, d, a, b, pu32Block[14], MD5_S13, (uint32_t) 2792965006u); /* 15 */
    MD5_FF ( b, c, d, a, pu32Block[15], MD5_S14, (uint32_t) 1236535329u); /* 16 */

    /* Round 2 */
    MD5_GG ( a, b, c, d, pu32Block[ 1], MD5_S21, (uint32_t) 4129170786u); /* 17 */
    MD5_GG ( d, a, b, c, pu32Block[ 6], MD5_S22, (uint32_t) 3225465664u); /* 18 */
    MD5_GG ( c, d, a, b, pu32Block[11], MD5_S23, (uint32_t)  643717713u); /* 19 */
    MD5_GG ( b, c, d, a, pu32Block[ 0], MD5_S24, (uint32_t) 3921069994u); /* 20 */
    MD5_GG ( a, b, c, d, pu32Block[ 5], MD5_S21, (uint32_t) 3593408605u); /* 21 */
    MD5_GG ( d, a, b, c, pu32Block[10], MD5_S22, (uint32_t)   38016083u); /* 22 */
    MD5_GG ( c, d, a, b, pu32Block[15], MD5_S23, (uint32_t) 3634488961u); /* 23 */
    MD5_GG ( b, c, d, a, pu32Block[ 4], MD5_S24, (uint32_t) 3889429448u); /* 24 */
    MD5_GG ( a, b, c, d, pu32Block[ 9], MD5_S21, (uint32_t)  568446438u); /* 25 */
    MD5_GG ( d, a, b, c, pu32Block[14], MD5_S22, (uint32_t) 3275163606u); /* 26 */
    MD5_GG ( c, d, a, b, pu32Block[ 3], MD5_S23, (uint32_t) 4107603335u); /* 27 */
    MD5_GG ( b, c, d, a, pu32Block[ 8], MD5_S24, (uint32_t) 1163531501u); /* 28 */
    MD5_GG ( a, b, c, d, pu32Block[13], MD5_S21, (uint32_t) 2850285829u); /* 29 */
    MD5_GG ( d, a, b, c, pu32Block[ 2], MD5_S22, (uint32_t) 4243563512u); /* 30 */
    MD5_GG ( c, d, a, b, pu32Block[ 7], MD5_S23, (uint32_t) 1735328473u); /* 31 */
    MD5_GG ( b, c, d, a, pu32Block[12], MD5_S24, (uint32_t) 2368359562u); /* 32 */

    /* Round 3 */
    MD5_HH ( a, b, c, d, pu32Block[ 5], MD5_S31, (uint32_t) 4294588738u); /* 33 */
    MD5_HH ( d, a, b, c, pu32Block[ 8], MD5_S32, (uint32_t) 2272392833u); /* 34 */
    MD5_HH ( c, d, a, b, pu32Block[11], MD5_S33, (uint32_t) 1839030562u); /* 35 */
    MD5_HH ( b, c, d, a, pu32Block[14], MD5_S34, (uint32_t) 4259657740u); /* 36 */
    MD5_HH ( a, b, c, d, pu32Block[ 1], MD5_S31, (uint32_t) 2763975236u); /* 37 */
    MD5_HH ( d, a, b, c, pu32Block[ 4], MD5_S32, (uint32_t) 1272893353u); /* 38 */
    MD5_HH ( c, d, a, b, pu32Block[ 7], MD5_S33, (uint32_t) 4139469664u); /* 39 */
    MD5_HH ( b, c, d, a, pu32Block[10], MD5_S34, (uint32_t) 3200236656u); /* 40 */
    MD5_HH ( a, b, c, d, pu32Block[13], MD5_S31, (uint32_t)  681279174u); /* 41 */
    MD5_HH ( d, a, b, c, pu32Block[ 0], MD5_S32, (uint32_t) 3936430074u); /* 42 */
    MD5_HH ( c, d, a, b, pu32Block[ 3], MD5_S33, (uint32_t) 3572445317u); /* 43 */
    MD5_HH ( b, c, d, a, pu32Block[ 6], MD5_S34, (uint32_t)   76029189u); /* 44 */
    MD5_HH ( a, b, c, d, pu32Block[ 9], MD5_S31, (uint32_t) 3654602809u); /* 45 */
    MD5_HH ( d, a, b, c, pu32Block[12], MD5_S32, (uint32_t) 3873151461u); /* 46 */
    MD5_HH ( c, d, a, b, pu32Block[15], MD5_S33, (uint32_t)  530742520u); /* 47 */
    MD5_HH ( b, c, d, a, pu32Block[ 2], MD5_S34, (uint32_t) 3299628645u); /* 48 */

    /* Round 4 */
    MD5_II ( a, b, c, d, pu32Block[ 0], MD5_S41, (uint32_t) 4096336452u); /* 49 */
    MD5_II ( d, a, b, c, pu32Block[ 7], MD5_S42, (uint32_t) 1126891415u); /* 50 */
    MD5_II ( c, d, a, b, pu32Block[14], MD5_S43, (uint32_t) 2878612391u); /* 51 */
    MD5_II ( b, c, d, a, pu32Block[ 5], MD5_S44, (uint32_t) 4237533241u); /* 52 */
    MD5_II ( a, b, c, d, pu32Block[12], MD5_S41, (uint32_t) 1700485571u); /* 53 */
    MD5_II ( d, a, b, c, pu32Block[ 3], MD5_S42, (uint32_t) 2399980690u); /* 54 */
    MD5_II ( c, d, a, b, pu32Block[10], MD5_S43, (uint32_t) 4293915773u); /* 55 */
    MD5_II ( b, c, d, a, pu32Block[ 1], MD5_S44, (uint32_t) 2240044497u); /* 56 */
    MD5_II ( a, b, c, d, pu32Block[ 8], MD5_S41, (uint32_t) 1873313359u); /* 57 */
    MD5_II ( d, a, b, c, pu32Block[15], MD5_S42, (uint32_t) 4264355552u); /* 58 */
    MD5_II ( c, d, a, b, pu32Block[ 6], MD5_S43, (uint32_t) 2734768916u); /* 59 */
    MD5_II ( b, c, d, a, pu32Block[13], MD5_S44, (uint32_t) 1309151649u); /* 60 */
    MD5_II ( a, b, c, d, pu32Block[ 4], MD5_S41, (uint32_t) 4149444226u); /* 61 */
    MD5_II ( d, a, b, c, pu32Block[11], MD5_S42, (uint32_t) 3174756917u); /* 62 */
    MD5_II ( c, d, a, b, pu32Block[ 2], MD5_S43, (uint32_t)  718787259u); /* 63 */
    MD5_II ( b, c, d, a, pu32Block[ 9], MD5_S44, (uint32_t) 3951481745u); /* 64 */

    pu32State[0]	+= a;
    pu32State[1]	+= b;
    pu32State[2]	+= c;
    pu32State[3]	+= d;
}

void	naMD5Checksum::GetChecksum( uint8_t *pu8Checksum )
{
    uint32_t	u32Input[16];
    uint32_t	u32Index = 0, u32PadLen = 0;

    u32Input[14]	= m_stContext.au32Count[0];
    u32Input[15]	= m_stContext.au32Count[1];

    u32Index	= (uint32_t)( ( m_stContext.au32Count[0] >> 3 ) & 0x3F );

    u32PadLen	= ( u32Index < 56 ) ? ( 56 - u32Index ) : ( 120 - u32Index );
    Update( const_cast<uint8_t*>( g_u8MDPaddingTable ), u32PadLen );

    EA_TO_LITTLEENDIANS_32BIT( u32Input, (uint32_t *) m_stContext.abyInput, 14 );
    Transform( u32Input );

    EA_TO_LITTLEENDIANS_32BIT( (uint32_t *) pu8Checksum, m_stContext.au32State, 4 );
}

std::string naMD5Checksum::GetChecksumAsString_s()
{
    uint8_t aChecksum[16];
    char szText[32+1];

    GetChecksum( aChecksum );
    for( int i=0; i < 16; i++ ) {
        sprintf( szText + (i*2), "%02X", aChecksum[i] );
    }
    return szText;
}

