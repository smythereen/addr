# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
# Copyright (c) 2011-2026 John R. Smythe Jr.
#

#
#	Global Definitions
#

include		../rules.mak

#
#	Unit and Common Header Definitions
#

CHDRS =	$(HDR)/$(UNIT).h	\
	$(HDR)/$(UNIT)mem.h

#
#	Unit's Library Definitions
#

LIBRARIES =	-lmio	\
		-lmap	\
		-lsem	\
		-lnow	\
		-lsys

#
#	Product Definitions
#
#	The programs (addr, addrmem) and the script addr_init.sh are found
#	automatically.  The old *.msg name tables are only kept, in .save, as
#	a reference for filling in addr_init.sh.
#

#
#	Global Targets
#

include		../targets.mak

#
#	Unit's Targets
#


#
#	Include	Object Dependency Files
#

include	.depend
