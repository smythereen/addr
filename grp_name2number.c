/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	This file defines the following function.
 *		Group_Name_To_Number( );
 ******************************************************************************/
#include	"addrlocal.h"

/* FUNCTION:	Group_Name_To_Number
 *
 *	DESCRIPTION:
 *		This subroutine will return the integer value of the group
 *		name
 *
 *	INPUTS:
 *		Group name or number string
 *
 *	RETURNS:
 *		integer group number
 *
 *	ON ERROR:
 *		N/A
 */

int	Group_Name_To_Number( char * name )
{
	int		i;
	addr_name_t	x = { .value = (u64)0 };

	if( name != NULL && isdigit( *name ) ) {
		i =  ( strtol( name, 0, 0 ) & 0xFF );
		return( ( i & GRP_PID ) == 0 || i == 0xFF ? i : GRP_PID );
	}
	if( name != NULL && strcasecmp( name, "pid" ) == 0 ) return( GRP_PID );
	if( name != NULL && strcasecmp( name, "all" ) == 0 ) return( 255 );

	if( addrmem != NULL || Addr_Map( ) != NULL ) {
		if(	name == NULL			||
			*name == 0			||
			strcasecmp( name, "loc" )   == 0 ||
			strcasecmp( name, "local" ) == 0 ) return( (int)addrmem->loc_grp );
		strncpy( x.name, name, sizeof( x.name ) );
		for( i = 0; i <= GRP_PID; i += 1 ) {
			if( x.value == addrmem->grp[ i ].value ) return( i );
		}
	}
	Trace(  0,  "Group_Name_To_Number: Unknown Group Name \"%s\"", name );
	FatalError( "Group_Name_To_Number: Unknown Group Name \"%s\"", name );
	return( -1 ); 
}
