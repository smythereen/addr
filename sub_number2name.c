/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	This file defines the following function.
 *		SubTask_Number_To_Name( );
 ******************************************************************************/
#include	"addrlocal.h"

/* FUNCTION:	SubTask_Number_To_Name
 *
 *	DESCRIPTION:
 *		This subroutine will return the sub-task name from the
 *		integer sub-task value
 *
 *	INPUTS:
 *		integer sub-task number
 *
 *	RETURNS:
 *		sub-task name or number string
 *
 *	ON ERROR:
 *		N/A
 */

char *	SubTask_Number_To_Name( int subtask )
{
static	char		buf[ 16 ];

	if( subtask <   0 ) subtask =   0;
	if( subtask > 255 ) subtask = 255;

	if( addrmem == NULL && Addr_Map( ) == NULL ) {
		sprintf( buf, "%u", (uchar)subtask );	/* no addr.mem: show the number */
		return( buf );
	}

	if( addrmem->sub[ subtask ].value != 0 ) {
		strncpy( buf, addrmem->sub[ subtask ].name, sizeof( addrmem->sub[ subtask ].name ) );
		buf[ sizeof( addrmem->sub[ subtask ].name ) ] = 0;
	} else {
		sprintf( buf, "%u", (uchar)subtask );
	}
	return( buf ); 
}


