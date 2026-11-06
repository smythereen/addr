/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	This file defines the following function.
 *		SubTask_Name_To_Number( );
 ******************************************************************************/
#include	"addrlocal.h"

/* FUNCTION:	SubTask_Name_To_Number
 *
 *	DESCRIPTION:
 *		This subroutine will return the integer value of the SubTask
 *		name
 *
 *	INPUTS:
 *		SubTask name or number string
 *
 *	RETURNS:
 *		integer SubTask number
 *
 *	ON ERROR:
 *		N/A
 */

int	SubTask_Name_To_Number( char * name )
{
	int		i;
	addr_name_t	x = { .value = (u64)0 };

	if( name == NULL || *name == 0 || strcasecmp( name, "all" ) == 0 ) return( 255 );
	if( isdigit( *name ) ) return( ( strtol( name, 0, 0 ) & 0xFF ) );
	if( addrmem != NULL || Addr_Map( ) != NULL ) {
		strncpy( x.name, name, sizeof( x.name ) );
		for( i = 0; i < 256; i += 1 ) {
			if( x.value == addrmem->sub[ i ].value ) return( i );
		}
	}
	Trace(  0,  "SubTask_Name_To_Number: Unknown Sub-Task Name \"%s\"", name );
	FatalError( "SubTask_Name_To_Number: Unknown Sub-Task Name \"%s\"", name );
	return( -1 ); 
}
