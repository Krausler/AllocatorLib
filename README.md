Allocator Library (ALL)
=======================
AllocatorLib is an all purpose heap allocator with custom std types for Lists, HashMaps (not implemented) and Vectors (not implemented).

# Getting Started
ALL uses premake as it's build system. To build ALL Windows is recommended, however building for linux is possible.

To get started clone this repository.

__Building ALL for Windows:__

<ins>**Option 1 - Integrate ALL into an existing premake project:**</ins>

1. To integrate ALL in to a project, inclution of [premake5.lua](AllocatorLib/premake5) located in the `AllocatorLib` folder is needed. Do this by inserting `include "path/to/library/AllocatorLib"` into the projects workspace file. Note: Do not include the [premake5.lua](premake5.lua) file located in the root directory of this project.

![Include](Resources/Include-Image.png?raw=true "Include")

2. Now add a `links {"AllocatorLib"}` statement into the premake project file in which ALL should be used in.

![Include](Resources/Links-Image.png?raw=true "Include")

3. Reload your premake project and everything should be up and ready.

<ins>**Option 2 - Building ALL staticly using Visual Studio:**</ins>

1. Execute [Setup-Visual-Studio.bat](Scripts/Setup-Visual-Studio.bat) located in the `Scripts` folder. This will generate a Visual Studio solution file.
2. Open the solution file and make sure to selct Dist ofr the building configuration. Then right click on the AllocatorLib project and select build.
![Include](Resources/Build-And-Dist.png?raw=true "Include")
4. There will be a static library generated in the `bin/Dist-windows-x86_64/AllocatorLib` folder.

<ins>**Option 3 - Building ALL staticly using make:**</ins>

1. Execute [Setup-Visual-Studio.bat](Scripts/Build-AllocatorLib.bat) located in the `Scripts folder`. This will generate a static library in `bin/Dist-windows-Your-Computer-Architecture/AllocatorLib`. Note: Building ALL this way requires make and gcc to be installed.

__Building ALL for Linux:__

1. Execute [Setup-Visual-Studio.bat](Scripts/Build-AllocatorLib.bat) located in the `Scripts folder`. This will generate a static library in `bin/Dist-linux-Your-Computer-Architecture/AllocatorLib`. Note: Building ALL this way requires make and gcc to be installed.
