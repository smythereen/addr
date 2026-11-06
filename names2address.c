/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	This file defines the following function.
 *		Names_To_Address( );
 ******************************************************************************/
#include	"addrlocal.h"

/* FUNCTION:	Names_To_Address
 *
 *	DESCRIPTION:
 *		This subroutine will return the integer value of the program
 *		number field of the address argument.
 *
 *	INPUTS:
 *		machine name
 *		group name
 *		program name
 *		sub-task name
 *
 *	RETURNS:
 *		message system ADDRESS
 *
 *	ON ERROR:
 *		N/A
 */

u32	Names_To_Address(	char *	mch,
				char *	grp,
				char *	prg,
				char *	sub
	)
{
	int	m = Machine_Name_To_Number( mch );
	int	g = Group_Name_To_Number( grp );
	int	p = Program_Name_To_Number( prg );
	int	s;
	if( (uchar)g != GRP_PID ) {
		s = SubTask_Name_To_Number( sub );
		return( Numbers_To_Address( m, g, p, s ) );
	}
	if( p == 0 ) p = getpid( );
	return( Numbers_To_Address( m, g, p, 0 ) );
}


