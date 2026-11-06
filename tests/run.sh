#!/bin/bash
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
# Copyright (c) 2026 John R. Smythe Jr.
#	addr unit tests.  Usage: tests/run.sh   (from the addr unit directory or anywhere)
#
#	Uses a private MEMORY_PATH, so the real addr.mem and addr_init.sh are never touched.
cd "$(dirname "$0")" || exit 1
ROOT=$(cd ../.. && pwd)
T=$(mktemp -d /tmp/addr_test.XXXXXX) || exit 1
trap 'rm -rf $T' EXIT
LIBS="-laddr -lmap -lsem -lmap -lnow -lfar -lsys -lmio"
gcc -g -w -I.. -I$ROOT/cmn addr_test.c -L$ROOT/lib $LIBS -o $T/addr_test || exit 1
rc=0

# 1. no addr.mem at all
mkdir $T/none
MEMORY_PATH=$T/none/ FILE_PATH=$T/none/ DATA_PATH=$T/none/ $T/addr_test notables || rc=1

# 2. addr.mem loaded with the addrmem program (the way addr_init.sh does it)
mkdir $T/tab
export MEMORY_PATH=$T/tab/ FILE_PATH=$T/tab/ DATA_PATH=$T/tab/
AM=$ROOT/bin/addrmem
$AM loc_mch 5 > /dev/null
$AM loc_grp 6 > /dev/null
$AM 'mch[1].name' c00 > /dev/null
$AM 'grp[2].name' grp > /dev/null
$AM 'prg[3].name' prg > /dev/null
$AM 'sub[4].name' sub > /dev/null
$T/addr_test tables || rc=1

# 3. the addr program
A=$ROOT/bin/addr
$A name2address c00.grp.prg.sub | grep -q '0x01020304 = c00.grp.prg.sub' || { echo "FAIL addr name2address"; rc=1; }
$A address2name 01020304      | grep -q '0x01020304 = c00.grp.prg.sub' || { echo "FAIL addr address2name"; rc=1; }
$A m_na c00 | grep -q '= 1$' || { echo "FAIL addr m_na"; rc=1; }
$A m_nu 1   | grep -q '= c00$' || { echo "FAIL addr m_nu"; rc=1; }
[ $rc = 0 ] && echo "addr tests: PASS" || echo "addr tests: FAIL"
exit $rc
