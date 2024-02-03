include "Config.lua"

project "AllocatorLib"
    kind "None"
    language "C++"
    cppdialect "C++20"

    files
    {
        "src/Allocator/**.h",
        "src/Allocator/**.cpp"
    }


    if(BuildStaticLib == true) then
        kind "StaticLib"
        defines { "ALL_BUILD_STATIC_LIB" }
    end

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
		symbols "off"
		optimize "Speed"
		defines "ALL_DIST"