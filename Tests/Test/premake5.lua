project "Tester"
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
        "%{wks.location}/AllocatorLib/src",
        "AllocatorLib"
    }
    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
        defines "ALL_ENABLE_ASSERT"

    filter "configurations:Release"
		runtime "Release"
		optimize "Speed"

    filter "configurations:Dist"
		runtime "Release"
		symbols "off"
		optimize "Speed"