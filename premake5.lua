workspace "Project"
    architecture "x86_64"
    startproject "Application"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Core"
include "Application"


