cd ..
call "Vendor/premake/premake5.exe" gmake2
call make config=dist Tester
call make config=dist GTests
PAUSE