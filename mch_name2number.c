/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	This file defines the following function.
 *		Machine_Name_To_Number( );
 ******************************************************************************/
#include	<sys/utsname.h>
#include	"addrlocal.h"

/* FUNCTION:	Machine_Name_To_Number
 *
 *	DESCRIPTION:
 *		This subroutine will return the integer value of the machine
 *		name
 *
 *	INPUTS:
 *		machine name or number string
 *
 *	RETURNS:
 *		integer machine number
 *
 *	ON ERROR:
 *		N/A
 */

int	Machine_Name_To_Number( char * name )
{
	int		i;
	addr_name_t	x = { .value = (u64)0 };

	if( name != NULL && isdigit( *name ) ) return( ( strtol( name, 0, 0 ) & 0xFF ) );
	if( name != NULL && ( strcasecmp( name, "all" ) == 0 ) ) return( 255 );

	if( addrmem != NULL || Addr_Map( ) != NULL ) {
		if(	name == NULL			||
			*name == 0			||
			strcasecmp( name, "loc" )   == 0 ||
			strcasecmp( name, "local" ) == 0 ) return( (int)addrmem->loc_mch );
		strncpy( x.name, name, sizeof( x.name ) );
		for( i = 0; i < 256; i += 1 ) {
			if( x.value == addrmem->mch[ i ].value ) return( i );
		}
	}
	Trace(  0,  "Machine_Name_To_Number: Unknown Machine Name \"%s\"", name );
	FatalError( "Machine_Name_To_Number: Unknown Machine Name \"%s\"", name );
	return( -1 ); 
}
