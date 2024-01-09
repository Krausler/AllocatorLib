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

    filter "system:windows"

    filter "configurations:Debug"
		runtime "Debug"
        symbols "on"

        defines "AL_DEBUG"

    filter "configurations:Release"
		runtime "Release"
		optimize "Speed"

    filter "configurations:Dist"
		runtime "Release"
		optimize "Speed"
		symbols "off"