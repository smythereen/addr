/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Process To Send Internal Messages To Another Process
 *
 *	This file defines the following private functions.
 *		main( );
 ******************************************************************************/
#include	<mem_io.h>
#include	"addrlocal.h"


typedef	struct	list_s	{
	char *	cmd;
	void	(*func)( int ac, char * av[ ], ... );
}	list_t;

static	void	usage( char * av[ ] )
{
	fprintf( stderr,
		 "\n\tAddress System (ADDR) - Verification Program\n\n"
		 "Usage:\n"
		 "\t%s\t a[ddress2name]       hex_address\n"
		 "\t  \t a2g[roup_number]     hex_address\n"
		 "\t  \t a2m[achine_number]   hex_address\n"
		 "\t  \t a2p[rogram_number]   hex_address\n"
		 "\t  \t a2s[ubtask_number]   hex_address\n"
		 "\t  \t g_na[me2number]    [ group_name ]\n"
		 "\t  \t g_nu[mber2name]      group_number\n"
		 "\t  \t m_na[me2number]    [ machine_name ]\n"
		 "\t  \t m_nu[mber2name]      machine_number\n"
		 "\t  \t n[ame2address]       machine.group.program.task\n"
		 "\t  \t p_na[me2number]    [ program_name ]\n"
		 "\t  \t p_nu[mber2name]      program_number\n"
		 "\n",
		 av[ 0 ]
	);
	fflush( stderr );
	exit( 1 );
}

static	void	a2n( int ac, char * av[ ], ... )
{
	u32	adr;

	if( ac != 1 ) return;
	adr = strtoul( av[0], 0, 16 );
	printf( "\t0x%08X = %s\n", adr, Address_To_Name( adr, 0 ) );
	exit( 0 );
}

static	void	a2g( int ac, char * av[ ], ... )
{
	if( ac != 1 ) return;
	printf( "Address To Group Number = %d\n", Address_To_Group_Number( strtoul( av[0], 0, 16 ) ) );
	exit( 0 );
}

static	void	a2m( int ac, char * av[ ], ... )
{
	if( ac != 1 ) return;
	printf( "Address To Machine Number = %d\n", Address_To_Machine_Number( strtoul( av[0], 0, 16 ) ) );
	exit( 0 );
}

static	void	a2p( int ac, char * av[ ], ... )
{
	if( ac != 1 ) return;
	printf( "Address To Program Number = %d\n", Address_To_Program_Number( strtoul( av[0], 0, 16 ) ) );
	exit( 0 );
}

static	void	a2s( int ac, char * av[ ], ... )
{
	if( ac != 1 ) return;
	printf( "Address To SubTask Number = %d\n", Address_To_SubTask_Number( strtoul( av[0], 0, 16 ) ) );
	exit( 0 );
}

static	void	g_n2i( int ac, char * av[ ], ... )
{
	printf( "Group Name To Number = %d\n", Group_Name_To_Number( av[0] ) );
	exit( 0 );
}

static	void	g_i2n( int ac, char * av[ ], ... )
{
	if( ac != 1 ) return;
	printf( "Group Number To Name = %s\n", Group_Number_To_Name( strtoul( av[0], 0, 10 ) ) );
	exit( 0 );
}

static	void	m_n2i( int ac, char * av[ ], ... )
{
	printf( "Machine Name To Number = %d\n", Machine_Name_To_Number( av[0] ) );
	exit( 0 );
}

static	void	m_i2n( int ac, char * av[ ], ... )
{
	if( ac != 1 ) return;
	printf( "Machine Number To Name = %s\n", Machine_Number_To_Name( strtoul( av[0], 0, 10 ) ) );
	exit( 0 );
}

static	void	n2a( int ac, char * av[ ], ... )
{
	u32	adr;

	if( ac != 1 ) return;
	adr = Name_To_Address( av[0] );
	printf( "\t0x%08X = %s\n", adr, Address_To_Name( adr, 0 ) );
	exit( 0 );
}

static	void	p_n2i( int ac, char * av[ ], ... )
{
	printf( "Program Name To Number = %d\n", Program_Name_To_Number( av[0] ) );
	exit( 0 );
}

static	void	p_i2n( int ac, char * av[ ], ... )
{
	if( ac != 1 ) return;
	printf( "Program Number To Name = %s\n", Program_Number_To_Name( strtoul( av[0], 0, 10 ) ) );
	exit( 0 );
}

static	list_t	cmdlist[ ]	=	{
	{	"address2name",		a2n		},
	{	"a2group_number",	a2g		},
	{	"a2machine_number",	a2m		},
	{	"a2program_number",	a2p		},
	{	"a2subtask_number",	a2s		},
	{	"g_name2number",	g_n2i		},
	{	"g_number2name",	g_i2n		},
	{	"m_name2number",	m_n2i		},
	{	"m_number2name",	m_i2n		},
	{	"name2address",		n2a		},
	{	"p_name2number",	p_n2i		},
	{	"p_number2name",	p_i2n		},
	{	(char *)0,		0		}
};

int	main( int ac, char * av[ ] )
{
struct	list_s	*	l;
	int		len;

	LocalName = av[ 0 ];
	switch( ac ) {
	default:	len = strlen( av[ 1 ] );
			for( l = cmdlist; l->cmd != (char *)0; l++ ) {
				if( strncmp( av[ 1 ], l->cmd, len ) ) continue;
				l->func( ( ac - 2 ), &av[ 2 ] );
				break;
			}
	case  1:
	case  0:	usage( av );
	}
	exit( 0 );
}
