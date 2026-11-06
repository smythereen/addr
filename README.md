# addr — structured addresses and name lookup

`addr` represents a message address as a fixed-width `u32`, split into machine,
group, program, and subtask bytes. It supplies numeric decomposition, name
conversion, and a mapped name table. This is not an IP-address or DNS library.

## Public interface

- `addr.h`: `Addr_t`, `Numbers_To_Address`, `Address_To_*_Number`,
  `Name_To_Address`, `Names_To_Address`, `Address_To_Name`, and the four pairs
  of component name/number functions.
- `addrmem.h`: mapped-table layout plus `Addr_Map`, `Addr_Mem`, `Addr_Unmap`.
- `addrlocal.h` is an implementation header, not an aggregate application API.
- Old `MsgN2A`, `MsgA2N`, `MsgMachine`, and related names are compatibility
  macros in `addr.h`; define `ADDR_NO_MSG_NAMES` to omit them.

`Numbers_To_Address(1,2,3,4)` yields `0x01020304`. The layout includes endian
branches. PID groups use `GRP_PID` and a 23-bit process ID, rather than the
ordinary program/subtask interpretation. Name conversions use `addr.mem`;
returned name strings may be static, so copy them when retaining a result.

## Dependencies and build

Use this directory as `addr/` inside a [base](https://github.com/smythereen/base)
project, beside the root `rules.mak` and `targets.mak`:

```sh
export UNITS_CATALOG_URL=https://unit-catalog.dejavu-archive.workers.dev
./repo/repo.sh add addr
HOME=$PWD make -C addr header library product
```

Run the root build for the other selected units first. Headers are exported to
`cmn/`, the archive to `lib/libaddr.a`, and `addr`/`addrmem` to `bin/`.
The source snapshot has no `UNIT.deps`: the public starter currently supplies
the companion units, but a minimal custom project must declare them itself.
Direct source headers include `sys` (`common.h`), `far`, `map`, and `mio`
(`mem_io.h`); the supplied makefile links `mio map sem now sys`. `far` and
`atomic` also enter through the shared-unit dependency closure. Static linking
can require a linker group, as shown below.

GCC 14 requires the existing base flag `-Wno-implicit-int` for legacy
`addrmem.c`; this publication does not silently modernize its source.

## C and C++

This unit is usable from **C and C++**. Its public headers already supply
`extern "C"` guards, including the exported shared-memory header where present.
Compile the implementation `.c` files with GCC and link that C library into
your C++ application with G++; do not reinterpret the whole legacy C source
as C++. GNU language extensions and the POSIX/Linux environment are assumed.
No additional caller-side linkage wrapper is needed. Mutable string arguments
are represented by arrays, not C++ string literals cast to `char *`.

The following example is valid C and intended for GNU C++ as well:

```c
#include <addr.h>
int main(void) {
    u32 a = Numbers_To_Address(1, 2, 3, 4);
    return a != 0x01020304U || Address_To_Machine_Number(a) != 1;
}
```

Save it as `smoke.c` or use [`examples/smoke.c`](examples/smoke.c). From a
project root with headers in `cmn/` and built libraries in `lib/`:

```sh
gcc -std=gnu11 -Icmn addr/examples/smoke.c -Llib \
  -Wl,--start-group -laddr -lmio -lmap -lsem -lfar -lnow -lsys -Wl,--end-group -o addr-smoke
g++ -std=gnu++17 -x c++ -Icmn -c addr/examples/smoke.c -o addr-caller.o
g++ addr-caller.o -Llib \
  -Wl,--start-group -laddr -lmio -lmap -lsem -lfar -lnow -lsys -Wl,--end-group -o addr-smoke-cpp
```

Caller objects precede libraries; the GNU linker group handles cyclic static
unit dependencies. A narrower caller may need fewer libraries.

## Programs and tests

With a project-local runtime (not your production MEMORY_PATH), initialize
only the names you need through `bin/addrmem`, for example:

```sh
# Runtime directory paths must exist and follow base's environment conventions.
bin/addrmem loc_mch 5
bin/addrmem loc_grp 6
bin/addrmem 'mch[1].name' c00
bin/addrmem 'grp[2].name' grp
bin/addrmem 'prg[3].name' prg
bin/addrmem 'sub[4].name' sub
bin/addr name2address c00.grp.prg.sub
bin/addr address2name 01020304
bash addr/tests/run.sh
```

The supplied test runner uses temporary runtime directories and requires
already-built libraries plus `bin/addrmem` and `bin/addr`. It checks lookup
with and without tables, special names, PID handling, and the actual CLI.
The original host-specific `addr_init.sh` is deliberately not published;
these small table assignments illustrate project-owned initialization.

## Verification

All 14 source files compiled individually with GCC 14 and the base legacy
compatibility flag. The numeric API smoke example compiled, linked, and ran.
That is not a claim of a full clean base build or an execution of every
integration test. C++ linkage guards were inspected; a C++ compile/run was not
available in the publication environment because its C++ frontend was absent.

## Source and license

Published from the current Guardian unit directory as a clean snapshot, not
its private Git history. C/header/makefile bytes are preserved; build outputs,
backups, generated dependency files, and host deployment initialization are
excluded. New examples and this guide are documentation additions. No release
tag is created by this publication. See `LICENSE` and `LICENSES/` for the
existing Apache-2.0 OR GPL-2.0-or-later licensing.
