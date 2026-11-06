/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	This file defines the following function.
 *		Machine_Number_To_Name( );
 ******************************************************************************/
#include	"addrlocal.h"

/* FUNCTION:	Machine_Number_To_Name
 *
 *	DESCRIPTION:
 *		This subroutine will return the machine name from the
 *		integer machine value
 *
 *	INPUTS:
 *		integer machine number
 *
 *	RETURNS:
 *		machine name or number string
 *
 *	ON ERROR:
 *		N/A
 */

char *	Machine_Number_To_Name( int machine )
{
static	char		buf[ 16 ];

	if( machine <   0 ) machine =   0;
	if( machine > 255 ) machine = 255;

	if( addrmem == NULL && Addr_Map( ) == NULL ) {
		sprintf( buf, "%u", (uchar)machine );	/* no addr.mem: show the number */
		return( buf );
	}

	if( addrmem->mch[ machine ].value != 0 ) {
		strncpy( buf, addrmem->mch[ machine ].name, sizeof( addrmem->mch[ machine ].name ) );
		buf[ sizeof( addrmem->mch[ machine ].name ) ] = 0;
	} else {
		sprintf( buf, "%u", (uchar)machine );
	}
	return( buf ); 
}


