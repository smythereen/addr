/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Generates An ASCII Name From An Address
 *
 *	This file defines the following functions.
 *		Address_To_Name( );
 ******************************************************************************/
#include	"addrlocal.h"

/* FUNCTION:	Address_To_Name
 *
 *	DESCRIPTION:
 *		This subroutine will return a pointer to a character array
 *		which will contain a message system name from a
 *		message system ADDRESS
 *
 *	INPUTS:
 *		message system ADDRESS
 *
 *	RETURNS:
 *		str =	ASCII NAME
 *
 *	ON ERROR:
 *		Returns (char *)0 on any error
 */

char	*	Address_To_Name( u32 adr, char * buf )
{
static	char		buffer[ 64 ];
	char	*	m = Machine_Number_To_Name( Address_To_Machine_Number( adr ) );
	char	*	g;
	char	*	p;
	char	*	s;

	if( buf == (char *)0 ) buf = buffer;
	if( adr == 0 ) {
		strcpy( buf, "zero" );
		return( buf );
	}
	if( ( Address_To_Group_Number( adr ) & GRP_PID ) == 0 || Address_To_Group_Number( adr ) == 0xFF ) {
		g = Group_Number_To_Name(	Address_To_Group_Number(	adr ) );
		p = Program_Number_To_Name(	Address_To_Program_Number(	adr ) );
		s = SubTask_Number_To_Name(	Address_To_SubTask_Number(	adr ) );
		sprintf( buf, "%s.%s.%s.%s", m, g, p, s );
	} else {
		sprintf( buf, "%s.pid.%u.", m, ( adr & ~0xFF800000 ) );
	}
	return( buf );
}

