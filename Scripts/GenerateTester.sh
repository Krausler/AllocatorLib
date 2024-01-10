#!/bin/bash

cd ..
vendor/premake/premake5 gmake2
make config=dist Tester
read -p "Press Enter to continue..."
