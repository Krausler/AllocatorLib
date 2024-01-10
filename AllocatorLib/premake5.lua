project "AllocatorLib"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/Allocator/*.cpp",
        "src/Allocator/**.h"    
    }

    includedirs
    {
        "src"
    }

    filter "configurations:Debug"
		runtime "Debug"
        symbols "on"
        defines "ALL_DEBUG"

    filter "configurations:Release"
		runtime "Release"
		optimize "Speed"
        defines "ALL_RELEASE"

    filter "configurations:Dist"
		runtime "Release"
		optimize "Speed"
		symbols "off"
        defines "ALL_RELEASE"