/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */

#include	<map.h>
#include	"addrmem.h"

	addrmem_t	*	addrmem;

static	char	Addr_File[ ] = "addr.mem";

void	Addr_Unmap( int force )
{
	if( addrmem == NULL ) return;
	if( TracePointer == &addrmem->trace ) TracePointer = NULL;
	UnmapAddress( addrmem, force );
	addrmem = NULL;
}

addrmem_t *	Addr_Map( void )
{
	if( addrmem == NULL ) addrmem = MapFile2Mem( Addr_File, sizeof( addrmem_t ), PROT_WRITE );
//	if( addrmem != NULL && TracePointer == NULL ) TracePointer = &addrmem->trace;
	return( addrmem );
}

addrmem_t *	Addr_Mem( void )
{
	if( addrmem == NULL ) addrmem = MapFile( Addr_File );
//	if( addrmem != NULL && TracePointer == NULL ) TracePointer = &addrmem->trace;
	return( addrmem );
}
