/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	ADDR Shared Memory Header File
 *
 *	This file defines common structures, variables, and routines
 *	need for shared memory access.
 ******************************************************************************/
#ifndef	ADDRMEM_H
#define	ADDRMEM_H

#if	defined( __cplusplus )
extern	"C"	{
#endif

#include	<common.h>

typedef	union	addr_name_s	{
	char	name[ 8 ];
	u64	value;
}	addr_name_t;

/*
 *	ADDR Shared Memory Format
 */

typedef	struct	addrmem_s	{
	u32		trace;
	uchar		loc_mch;		/* Local Machine Number			*/
	uchar		loc_grp;		/* Local Group Number			*/
	char		spare[ 6 ];		/* spare				*/
	addr_name_t	mch[ 256 ];		/* Machine Name Table			*/
	addr_name_t	grp[ 256 ];		/* Group Name Table			*/
	addr_name_t	prg[ 256 ];		/* Program Name Table			*/
	addr_name_t	sub[ 256 ];		/* SubTask Name Table			*/
}	addrmem_t;

extern	addrmem_t	*	addrmem;

extern	addrmem_t *	Addr_Map( void );
extern	addrmem_t *	Addr_Mem( void );
extern	void		Addr_Unmap( int force );

#if	defined( __cplusplus )
}
#endif

#endif
