include "../Vendor/googletest/googletest"

project "GTests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.cpp",
        "src/**.h"    
    }

    includedirs
    {
        "../Vendor/googletest/googletest/include",
        ALLIncludeDir
    }

    links
    {
        "GoogleTest",
        "AllocatorLib"
    }
    
    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

    filter "configurations:Release"
		runtime "Release"
		optimize "Speed"

    filter "configurations:Dist"
		runtime "Release"
		symbols "off"
		optimize "Speed"