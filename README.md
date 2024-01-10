Allocator Library (All)
=======================
AllocatorLib is an all purpose heap allocator with custom std types for Lists, HashMaps (not implemented) and Vectors (not implemented).

# Getting Started
AllocatorLib uses premake5 for it's project build system generation.
You can implement All in multiple ways into your project:

__1. Build All as a static library__

    First clone the repo and change 'call "vendor/premake/premake5.exe" vs2022' in
    "GenerateProjects vs2022.bat" to 'call "vendor/premake/premake5.exe" gmake2'.
    This will generate make files for the project when "GenerateProjects vs2022.bat"
    is executed. 