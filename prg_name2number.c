/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	This file defines the following function.
 *		Program_Name_To_Number( );
 ******************************************************************************/
#include	"addrlocal.h"

/* FUNCTION:	Program_Name_To_Number
 *
 *	DESCRIPTION:
 *		This subroutine will return the integer value of the program
 *		name
 *
 *	INPUTS:
 *		program name or number string
 *
 *	RETURNS:
 *		integer program number
 *
 *	ON ERROR:
 *		N/A
 */

int	Program_Name_To_Number( char * name )
{
	int		i;
	addr_name_t	x = { .value = (u64)0 };

	if(	name == NULL			||
		*name == 0			||
		strcasecmp( name, "pid" )   == 0 ||
		strcasecmp( name, "loc" )   == 0 ||
		strcasecmp( name, "local" ) == 0 ) return( (int)( getpid( ) & ~0xFF800000 ) );

	if( isdigit( *name ) ) {
		i = strtol( name, 0, 0 );
		return( i != 0 ? i : (int)( getpid( ) & ~0xFF800000 ) );
	}
	if( strcasecmp( name, "all" ) == 0 ) return( 255 );

	if( addrmem != NULL || Addr_Map( ) != NULL ) {
		strncpy( x.name, name, sizeof( x.name ) );
		for( i = 0; i < 256; i += 1 ) {
			if( x.value == addrmem->prg[ i ].value ) return( i );
		}
	}
	Trace(  0,  "Program_Name_To_Number: Unknown Program Name \"%s\"", name );
	FatalError( "Program_Name_To_Number: Unknown Program Name \"%s\"", name );
	return( -1 ); 
}
