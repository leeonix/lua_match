
solution 'lua_match'
    location 'build'
    configurations { 'Debug', 'Release' }
    defines { 'WIN32', '_WINDOWS' }
    flags { 'StaticRuntime' }

    configuration 'vs*'
        defines { '_CRT_SECURE_NO_WARNINGS' }

    configuration 'Debug'
        flags { 'Symbols' }
        defines { '_DEBUG' }
        targetsuffix '_d'

    configuration 'Release'
        flags { 'Optimize' }
        defines { 'NDEBUG' }

project 'lua_match'
    language 'C++'
    kind 'StaticLib'
    targetdir 'lib'
    files
    {
        'src/*.h',
        'src/*.c',
        'src/*.hpp',
        'src/*.cpp',
    }

project 'test_c'
    language 'C'
    kind 'ConsoleApp'
    targetdir 'bin'

    includedirs 'src'
    files 'test/test.c'

    configuration 'Debug'
        links 'lib/lua_match_d'
    configuration 'Release'
        links 'lib/lua_match'

project 'test_cpp'
    language 'C++'
    kind 'ConsoleApp'
    targetdir 'bin'

    includedirs 'src'
    files 'test/test.cpp'

    configuration 'Debug'
        links 'lib/lua_match_d'
    configuration 'Release'
        links 'lib/lua_match'

