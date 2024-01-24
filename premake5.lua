workspace "AllocatorLib"
    architecture "x86_64"
    startproject "Tester"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "AllocatorLib" -- This line
include "Tester"


