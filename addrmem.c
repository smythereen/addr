/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Address Translation (ADDR) - Shared Memory Format
 ******************************************************************************/
#include	<map.h>
#include	<mem_io.h>
#include	<addrmem.h>

#define	STRUCT	addr_name_t
static	Mitem		addr_name_l[ ] =	{
	String(		name,		"Name"				),
	{ END_OF_LIST }
};
#undef	STRUCT

#define	STRUCT	addrmem_t
static	Mitem		addrmem_l[ ] =	{
	Xlong(		trace,		"Address Translation Trace Flags"	),
	Uchar(		loc_mch,	"Local Machine Number"			),
	Uchar(		loc_grp,	"Local Group Number"			),
	Struct(		addr_name_t,	mch,		addr_name_l		),
	Struct(		addr_name_t,	grp,		addr_name_l		),
	Struct(		addr_name_t,	prg,		addr_name_l		),
	Struct(		addr_name_t,	sub,		addr_name_l		),
	{ END_OF_LIST }
};
#undef	STRUCT

main( int ac, char * av[ ] )
{
	switch( ac ) {
	case 1:		break;
	default:	if( isalpha( *av[ 1 ] ) ) break;
	case 0:		fprintf( stderr,
				 "\nUsage:\n"
					"\t%s [ C.Variable.Name [ Value ] ]\n",
				 av[ 0 ]
			);
			fflush( stderr );
			exit( 1 );
	}
	LocalName = av[ 0 ];
	if( *LocalName == 'L' ) av[0] = 0;

	Addr_Map( );

	switch( ac ) {
	default:   Input_Memory_Item(  addrmem, addrmem_l, av[1], av[2] );
		   UpdateMap( addrmem, sizeof( addrmem_t ) );
	case  2:   Output_Memory_Item( addrmem, addrmem_l, av[1], av[0] );
		   break;
	case  1:   Output_Memory_Item( addrmem, addrmem_l,     0, av[0] );
		   break;
	}
	Addr_Unmap( 1 );
	exit( 0 );
}
