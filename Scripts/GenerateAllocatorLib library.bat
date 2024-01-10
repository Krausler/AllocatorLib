cd ..
call "vendor/premake/premake5.exe" gmake2
call make config=dist AllocatorLib
PAUSE