#!/bin/bash

cd ..
vendor/premake/premake5 gmake2
make config=dist AllocatorLib
read -p "Press Enter to continue..."
