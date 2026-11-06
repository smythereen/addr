/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	addr unit test: addresses, names, keywords and the old Msg* names.
 *
 *	usage:	addr_test tables	(MEMORY_PATH has an addr.mem loaded by run.sh)
 *		addr_test notables	(MEMORY_PATH has no addr.mem at all)
 ******************************************************************************/
#include	<addr.h>
#include	<addrmem.h>

static	int	fails;
static	int	checks;

#define	CHECK( cond )	do {							\
				checks += 1;					\
				if( !( cond ) ) {				\
					fails += 1;				\
					printf( "FAIL line %d: %s\n", __LINE__, #cond );	\
				}						\
			} while( 0 )

#define	SAME( a, b )	CHECK( strcmp( (a), (b) ) == 0 )

static	void	numbers( void )
{
	u32	a = Numbers_To_Address( 1, 2, 3, 4 );

	CHECK( a == 0x01020304 );
	CHECK( Address_To_Machine_Number( a ) == 1 );
	CHECK( Address_To_Group_Number( a ) == 2 );
	CHECK( Address_To_Program_Number( a ) == 3 );
	CHECK( Address_To_SubTask_Number( a ) == 4 );

	a = Numbers_To_Address( 255, 255, 255, 255 );	/* all.all.all.all */
	CHECK( a == 0xFFFFFFFF );
	CHECK( Address_To_Group_Number( a ) == 255 );

	a = Numbers_To_Address( 9, GRP_PID, 0x12345, 77 );	/* pid form: the subtask is dropped */
	CHECK( Address_To_Machine_Number( a ) == 9 );
	CHECK( Address_To_Group_Number( a ) == GRP_PID );
	CHECK( Address_To_Program_Number( a ) == 0x12345 );
	CHECK( Address_To_SubTask_Number( a ) == 0 );

	a = Numbers_To_Address( 9, GRP_PID, 0x3FFFFF, 0 );	/* biggest default linux pid (0x7F in the group byte would read as all) */
	CHECK( Address_To_Program_Number( a ) == 0x3FFFFF );

	CHECK( MsgFullAddress( 3, 4, 5, 6 ) == Numbers_To_Address( 3, 4, 5, 6 ) );	/* old names */
	CHECK( MsgMachine( 0x03040506 ) == 3 );
	CHECK( MsgGroup( 0x03040506 ) == 4 );
	CHECK( MsgProgram( 0x03040506 ) == 5 );
	CHECK( MsgSubTask( 0x03040506 ) == 6 );
}

static	void	tables( void )
{
	u32	a;

	SAME( Machine_Number_To_Name( 1 ), "c00" );
	SAME( Group_Number_To_Name( 2 ), "grp" );
	SAME( Program_Number_To_Name( 3 ), "prg" );
	SAME( SubTask_Number_To_Name( 4 ), "sub" );
	SAME( Machine_Number_To_Name( 200 ), "200" );	/* no name: the number */
	SAME( Group_Number_To_Name( 255 ), "all" );
	SAME( Group_Number_To_Name( GRP_PID ), "pid" );

	CHECK( Machine_Name_To_Number( "c00" ) == 1 );
	CHECK( Group_Name_To_Number( "grp" ) == 2 );
	CHECK( Program_Name_To_Number( "prg" ) == 3 );
	CHECK( SubTask_Name_To_Number( "sub" ) == 4 );

	CHECK( Machine_Name_To_Number( "17" ) == 17 );		/* numbers */
	CHECK( Machine_Name_To_Number( "0x11" ) == 17 );

	CHECK( Machine_Name_To_Number( "loc" ) == 5 );		/* keywords */
	CHECK( Machine_Name_To_Number( "LOCAL" ) == 5 );
	CHECK( Machine_Name_To_Number( NULL ) == 5 );
	CHECK( Machine_Name_To_Number( "all" ) == 255 );
	CHECK( Group_Name_To_Number( "loc" ) == 6 );
	CHECK( Group_Name_To_Number( "" ) == 6 );
	CHECK( Group_Name_To_Number( "pid" ) == GRP_PID );
	CHECK( Group_Name_To_Number( "ALL" ) == 255 );
	CHECK( Program_Name_To_Number( "all" ) == 255 );
	CHECK( Program_Name_To_Number( "pid" ) == ( getpid( ) & ~0xFF800000 ) );
	CHECK( SubTask_Name_To_Number( "all" ) == 255 );
	CHECK( SubTask_Name_To_Number( NULL ) == 255 );

	a = Name_To_Address( "c00.grp.prg.sub" );
	CHECK( a == 0x01020304 );
	SAME( Address_To_Name( a, 0 ), "c00.grp.prg.sub" );
	{
		char	buf[ 64 ];
		SAME( Address_To_Name( a, buf ), "c00.grp.prg.sub" );
		SAME( buf, "c00.grp.prg.sub" );
	}
	CHECK( Names_To_Address( "c00", "grp", "prg", "sub" ) == a );
	CHECK( Name_To_Address( "01020304" ) == 0x01020304 );	/* hex */
	CHECK( Name_To_Address( "0x01020304" ) == 0x01020304 );
	CHECK( Name_To_Address( "" ) == (u32)-1 );
	CHECK( Name_To_Address( NULL ) == (u32)-1 );

	CHECK( Name_To_Address( "zero" ) == 0 );
	SAME( Address_To_Name( 0, 0 ), "zero" );

	a = Name_To_Address( "c00.pid.4321." );			/* process id form */
	CHECK( Address_To_Group_Number( a ) == GRP_PID );
	CHECK( Address_To_Program_Number( a ) == 4321 );
	SAME( Address_To_Name( a, 0 ), "c00.pid.4321." );

	a = Name_To_Address( "pid" );				/* this process */
	CHECK( Address_To_Group_Number( a ) == GRP_PID );
	CHECK( Address_To_Program_Number( a ) == ( getpid( ) & ~0xFF800000 ) );
	CHECK( Address_To_Machine_Number( a ) == 5 );

	a = Name_To_Address( "c00.all.all.all" );
	CHECK( a == Numbers_To_Address( 1, 255, 255, 255 ) );

	CHECK( MsgN2A( "c00.grp.prg.sub" ) == 0x01020304 );	/* old names */
	SAME( MsgA2N( 0x01020304, 0 ), "c00.grp.prg.sub" );
	CHECK( MsgMachineInteger( "c00" ) == 1 );
	SAME( MsgGroupName( 2 ), "grp" );
	CHECK( MsgNames2Address( "c00", "grp", "prg", "sub" ) == 0x01020304 );
}

static	void	notables( void )
{
	CHECK( Addr_Mem( ) == NULL );
	SAME( Machine_Number_To_Name( 7 ), "7" );		/* no addr.mem: numbers */
	SAME( Group_Number_To_Name( 2 ), "2" );
	SAME( Program_Number_To_Name( 3 ), "3" );
	SAME( SubTask_Number_To_Name( 4 ), "4" );
	CHECK( Machine_Name_To_Number( "7" ) == 7 );
	CHECK( Group_Name_To_Number( "pid" ) == GRP_PID );
	CHECK( Group_Name_To_Number( "all" ) == 255 );
	CHECK( Name_To_Address( "7.2.3.4" ) == 0x07020304 );
	SAME( Address_To_Name( 0x07020304, 0 ), "7.2.3.4" );
}

int	main( int ac, char * av[ ] )
{
	LocalName = av[ 0 ];
	numbers( );
	if( ac > 1 && strcmp( av[ 1 ], "tables"   ) == 0 ) tables( );
	if( ac > 1 && strcmp( av[ 1 ], "notables" ) == 0 ) notables( );
	printf( "addr_test %s: %d checks, %d fails: %s\n", ac > 1 ? av[ 1 ] : "", checks, fails, fails ? "FAIL" : "PASS" );
	return( fails != 0 );
}
