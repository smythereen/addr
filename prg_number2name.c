/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	This file defines the following function.
 *		Program_Number_To_Name( );
 ******************************************************************************/
#include	"addrlocal.h"

/* FUNCTION:	Program_Number_To_Name
 *
 *	DESCRIPTION:
 *		This subroutine will return the program name from the
 *		integer program value
 *
 *	INPUTS:
 *		integer program number
 *
 *	RETURNS:
 *		Program name or number string
 *
 *	ON ERROR:
 *		N/A
 */

char *	Program_Number_To_Name( int program )
{
static	char		buf[ 16 ];

	if( program <= 0 ) program = getpid( );

	if( addrmem == NULL && Addr_Map( ) == NULL ) {
		sprintf( buf, "%u", (uchar)program );	/* no addr.mem: show the number */
		return( buf );
	}

	if( program < 256 && addrmem->prg[ program ].value != 0 ) {
		strncpy( buf, addrmem->prg[ program ].name, sizeof( addrmem->prg[ program ].name ) );
		buf[ sizeof( addrmem->prg[ program ].name ) ] = 0;
	} else {
		sprintf( buf, "%u", (uchar)program );
	}
	return( buf ); 
}


