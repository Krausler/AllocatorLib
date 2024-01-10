cd ..
call "vendor/premake/premake5.lua" gmake2
call make config=dist Tester
PAUSE