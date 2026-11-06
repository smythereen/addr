/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Generates An Address From ASCII Name
 *
 *	This file defines the following functions.
 *		Name_To_Address( );
 ******************************************************************************/
#include	"addrlocal.h"

#define	U16( a, b )	(u16)(a+(b<<8))

static	int	isxstring( char * s )
{
	if( *(u16*)s == U16('0','X') || *(u16*)s == U16('0','x') ) s += 2;
	while( *s != 0 ) if( !isxdigit( *s++ ) ) return( 0 );
	return( 1 );
}

/* FUNCTION:	Name_To_Address
 *
 *	DESCRIPTION:
 *		This subroutine will return a message system ADDRESS
 *		from a message system NAME "machine.group.program.task"
 *
 *	INPUTS:
 *		str =	ASCII NAME
 *
 *	RETURNS:
 *		message system ADDRESS
 *
 *	ON ERROR:
 *		Returns -1 on any error
 */

u32	Name_To_Address( char * str )
{
	char *	m;
	char *	g;
	char *	p;
	char *	s;
	char	buf[ MAX_PATH ];

	if( str == (char *)0 || *str == 0 ) return( (u32)-1 );
	if( strcasecmp( str, "zero" ) == 0 ) return( 0 );
	if( strcasecmp( str, "pid"  ) == 0 ) return( Names_To_Address( 0, "pid", 0, 0 ) );
	strncpy( buf, str, sizeof( buf ) - 1 );
	buf[ sizeof( buf ) - 1 ] = 0;
	str = buf;
	if( ( s = strrchr( str, '.' ) ) != (char *)0 ) {
		*s++ = 0;
		if( ( p = strrchr( str, '.' ) ) != (char *)0 ) {
			*p++ = 0;
			if( ( g = strrchr( str, '.' ) ) != (char *)0 ) {
				*g++ = 0;
				m = str;
			} else {
				m = (char *)0;
				g = str;
			}
		} else {
			m = (char *)0;
			g = (char *)0;
			p = str;
		}
	} else {
		if( isxstring( str ) ) return( strtoul( str, 0, 16 ) );
		m = (char *)0;
		g = (char *)0;
		p = (char *)0;
		s = str;
	}
	return( Names_To_Address( m, g, p, s ) );
}


