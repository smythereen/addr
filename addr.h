/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Address/Number To Name Routines
 *	Name To Address/Number Routines
 *
 *	An address is a u32: machine.group.program.subtask, one byte each.
 *	A group with the GRP_PID bit set is a "process id" address: the
 *	program and subtask bytes together hold a 23 bit process id.
 *
 *	The names of machines, groups, programs and subtasks live in the shared
 *	memory file addr.mem (see addrmem.h and addr_init.sh).
 *
 *	The old message system names (MsgA2N, MsgN2A, MsgMachine ...) are kept
 *	as macros for the new names, so existing sources compile unchanged.
 *	Define ADDR_NO_MSG_NAMES before including this file to turn them off.
 ******************************************************************************/
#ifndef	ADDR_H
#define	ADDR_H

#if	defined( __cplusplus )
extern	"C"	{
#endif

#include	<common.h>

/*
 *	External Definitions
 */

#ifndef	GRP_PID
#define	GRP_PID		((uchar)0x80)
#endif
#define	ADDR_TRC_LVL	0x10000000

/*
 *	General Address Format Structures
 */

typedef	union	Addr_s	{
	u32	addr;
	struct	{
#if __BYTE_ORDER == __BIG_ENDIAN
		u8	mch;
		u8	grp;
		u8	prg;
		u8	sub;
#else
		u8	sub;
		u8	prg;
		u8	grp;
		u8	mch;
#endif
	};
}	Addr_t;

/*
 *	Name To Number Routines
 *
 *	The keywords "loc"/"local" (this machine/group), "pid" (process
 *	group) and "all" (255) are understood in place of a name.
 */

extern	int	Machine_Name_To_Number(	char *	machine_name	);
extern	int	  Group_Name_To_Number(	char *	group_name	);
extern	int	Program_Name_To_Number(	char *	program_name	);
extern	int	SubTask_Name_To_Number(	char *	subtask_name	);

/*
 *	Number To Name Routines (the returned string is static)
 */

extern	char *	Machine_Number_To_Name(	int	machine_number	);
extern	char *	  Group_Number_To_Name(	int	group_number	);
extern	char *	Program_Number_To_Name(	int	program_number	);
extern	char *	SubTask_Number_To_Name(	int	subtask_number	);

/*
 *	Address Pieces
 */

static	inline	__attribute__((always_inline))	int	Address_To_Machine_Number( u32 x )
{
	return( (int)((Addr_t*)&x)->mch );
}

static	inline	__attribute__((always_inline))	int	Address_To_Group_Number( u32 x )
{
	u8	g = ((Addr_t*)&x)->grp;

	return( g != 0xFF && ( g & GRP_PID ) == GRP_PID ? (int)GRP_PID : (int)g );
}

static	inline	__attribute__((always_inline))	int	Address_To_Program_Number( u32 x )
{
	return(	Address_To_Group_Number( x ) != GRP_PID	?
		(int)((Addr_t*)&x)->prg			:
		(int)( x & ~0xFF800000 )
	);
}

static	inline	__attribute__((always_inline))	int	Address_To_SubTask_Number( u32 x )
{
	return(	Address_To_Group_Number( x ) != GRP_PID	?
		(int)((Addr_t*)&x)->sub			:
		0
	);
}

static	inline	__attribute__((always_inline))	u32	Numbers_To_Address(
		int	Machine,
		int	Group,
		int	Program,
		int	SubTask
)
{
	Addr_t	a;

	a.addr = 0;
	a.mch = (u8)Machine;
	if( ( (uchar)Group & GRP_PID ) != GRP_PID || (uchar)Group == 0xFF ) {
		a.grp = (u8)Group;
		a.prg = (u8)Program;
		a.sub = (u8)SubTask;
	} else {
		a.addr |= (u32)( Program & ~0xFF800000 );
		a.grp  |= GRP_PID;
	}
	return( a.addr );
}

/*
 *	Whole Address Routines
 */

extern	char *	Address_To_Name(	u32	address,
					char *	optional_buffer
	);


extern	u32	Name_To_Address(	char *	full_name
	);


extern	u32	Names_To_Address(	char *	machine_name,
					char *	group_name,
					char *	program_name,
					char *	subtask_name
	);

/*
 *	Old Message System Names
 */

#ifndef	ADDR_NO_MSG_NAMES

#define	MsgMachineInteger	Machine_Name_To_Number
#define	MsgGroupInteger		  Group_Name_To_Number
#define	MsgProgramInteger	Program_Name_To_Number
#define	MsgSubTaskInteger	SubTask_Name_To_Number

#define	MsgMachineName		Machine_Number_To_Name
#define	MsgGroupName		  Group_Number_To_Name
#define	MsgProgramName		Program_Number_To_Name
#define	MsgSubTaskName		SubTask_Number_To_Name

#define	MsgMachine		Address_To_Machine_Number
#define	MsgGroup		Address_To_Group_Number
#define	MsgProgram		Address_To_Program_Number
#define	MsgSubTask		Address_To_SubTask_Number

#define	MsgFullAddress		Numbers_To_Address

#define	MsgA2N			Address_To_Name
#define	MsgN2A			Name_To_Address
#define	MsgNames2Address	Names_To_Address

#endif

#if	defined( __cplusplus )
}
#endif

#endif
