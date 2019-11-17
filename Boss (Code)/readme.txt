BUILD INSTRUCTIONS
~~~~~~~~~~~~~~~~~~

I removed as many dependencies as possible. To make this easier to build

This means no:
- font
- audio

Build Environment
~~~~~~~~~~~~~~~~~~

- MingGW-w64
    - Download and install this (I install to d:\MinGW-w64)
    - Set Environment paths to point to the MinGW-w64\bin folder
    - duplicate mingw32-make.exe and name the duplicate make.exe

- MSYS2.0 64 Bit
    - Download and install this

- I used CodeBlocks as my IDE v17.12. Download and install this.
    - Once done go to the settings menu compiler and add a new compiler called
        'MinGW-w64' setup the paths to point to your MinGW-w64

- I use CMake. Any version should do. Download and install this.

DEPENDENCIES
~~~~~~~~~~~~~~~~~~

- Lua 5.1.0

    - Download source from the web

    - Install to MinGW-w64\libraries\lua-5.1.0 folder

    - Slight modification to a make file. This change ensures
        the build process will generate the "liblua.a" file.

        If you skip this step you will not get an object to link against. You will only get an exe and a dll.

        open "src/makefile"" with a text editor

        search for the 'Mingw:' and past in the following code over the top of the existing text:

        mingw:
            $(MAKE) "LUA_A=lua51.dll" "LUA_T=lua.exe" \
            "AR=$(CC) -shared -o" "RANLIB=strip --strip-unneeded" \
            "MYCFLAGS=-DLUA_BUILD_AS_DLL" "MYLIBS=" "MYLDFLAGS=-s" lua.exe
            $(MAKE) "LUAC_T=luac.exe" luac.exe

    - Then open up MSYS2.0 64bit navigate to the lua install location

    - Type ""make mingw" push enter

    - this should build the files you need your dll (liblua51.dll, liblua.a) in the src folder

    - In codeblocks, add the global variable for your lua library as lua-510
        Mine looks like this
        Base -> D:\MinGW-w64\libraries\lua-5.1
        Include -> D:\MinGW-w64\libraries\lua-5.1\src
        Lib -> D:\MinGW-w64\libraries\lua-5.1\lib

- GLFW-3.2.1

    - Download this library

    - Slight Modification to file src\input.c

        GLFWAPI int glfwGetKey(GLFWwindow* handle, int key)
        {
            ...
            /* #DodgeeSoftware @DodgeeSoftware (Shem Taylor) restored this method to function like the old GLFW */
            // if (key < GLFW_KEY_SPACE || key > GLFW_KEY_LAST)
            if (key < 0 || key > GLFW_KEY_LAST)
            ..
        }

        This change ensures that all keys can be tested against. If you don't make this change my GameInput system will throw an exception.
        I asked the developer of GLFW to fix this, but ended up just modifying the lirbary myself.

    - Open CMake, point at the install path of your GLFW-3.2.1 folder click config.
        Choose CodeBlocks - MinGW makefiles
        check specify native compilers
        Your c compiler should be "D:/MinGW-w64/bin/gcc.exe"
        Your c++ compiler should be "D:/MinGW-w64/bin/g++.exe"
        fortran compiler doesn't matter
        click finish
        You might need to tinker with some of the settings here. I dont' build the examples.
        then click generate. After that you should have a cbp file. You can open that in codeblocks. Go to build and build.

    - In codeblocks, add the global variable for your lua library as glfw-3.2.1
        Mine looks like this
        Base -> D:\MinGW-w64\libraries\glfw-3.2.1
        Include -> D:\MinGW-w64\libraries\glfw-3.2.1\include
        Lib -> D:\MinGW-w64\libraries\glfw-3.2.1\lib

- Download LuaBridge
    - This is a header only library no need to build
    - Install into d:/mingw-w64/lubraries/luabridge
    - Add this to your globals in codeblocks
        Mine looks like this
        Base -> D:\MinGW-w64\libraries\LuaBridge-2.4
        Include -> D:\MinGW-w64\libraries\LuaBridge-2.4\Source

- Copy the following into the exectuable folder of the boss project.
    Boss-Project-MinGW-w64\Boss (Executable)\

    libgcc_s_seh-1.dll (From d:\MinGW-w64\bin)
    libstdc++-6.dll (From d:\MinGW-w64\bin)
    libwinpthread-1.dll (From d:\MinGW-w64\bin)
    lua51.dll (From D:\MinGW-w64\libraries\lua-5.1\src)

- Open Boss.cbp in codeblocks build and run.


You can reach me at dodgeesoftware@gmail.com
