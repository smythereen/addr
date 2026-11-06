/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	This file defines the following function.
 *		Group_Number_To_Name( );
 ******************************************************************************/
#include	"addrlocal.h"

/* FUNCTION:	Group_Number_To_Name
 *
 *	DESCRIPTION:
 *		This subroutine will return the group name from the
 *		group integer value
 *
 *	INPUTS:
 *		integer group number
 *
 *	RETURNS:
 *		Group name or number string
 *
 *	ON ERROR:
 *		N/A
 */

char *	Group_Number_To_Name( int group )
{
static	char		buf[ 16 ];

	if( group <   0 ) group =   0;
	if( group > 255 ) group = 255;

	if( (uchar)group == 0xFF ) return( "all" );

	if( ( (uchar)group & GRP_PID ) != 0 ) return( "pid" );

	if( addrmem == NULL && Addr_Map( ) == NULL ) {
		sprintf( buf, "%u", (uchar)group );	/* no addr.mem: show the number */
		return( buf );
	}

	if( addrmem->grp[ group ].value != 0 ) {
		strncpy( buf, addrmem->grp[ group ].name, sizeof( addrmem->grp[ group ].name ) );
		buf[ sizeof( addrmem->grp[ group ].name ) ] = 0;
	} else {
		sprintf( buf, "%u", (uchar)group );
	}
	return( buf ); 
}


