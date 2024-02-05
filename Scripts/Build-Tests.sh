#!/bin/bash

cd ..
Vendor/premake/premake5 gmake2
make config=dist Tester
make config=dist GTests
read -p "Press Enter to continue..."
