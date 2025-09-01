#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
env.Append(CXXFLAGS=['/std:c++latest'])
VariantDir('build', 'src', duplicate=0)

sources = Glob("build/*.cc") + Glob("build/**/*.cc")


if env["platform"] == "macos":
    library = env.SharedLibrary(
        f"game/bin/lib.{env['platform']}.{env['target']}.framework/lib.{env['platform']}.{env['target']}",
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            f"game/bin/lib.{env['platform']}.{env['target']}.simulator.a",
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            f"game/bin/lib.{env['platform']}.{env['target']}.a",
            source=sources,
        )
else:
    library = env.SharedLibrary(
        f"game/bin/lib{env['suffix']}{env['SHLIBSUFFIX']}",
        source=sources,
    )

Default(library)
