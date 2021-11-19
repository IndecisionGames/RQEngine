workspace "RQEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations { "Debug", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "RQEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/**.h",
		"src/**.cpp"
	}

	includedirs
	{
        "include",
        "lib/third-party/SDL2-w64/include",
        "lib/third-party/glew-2.2.0/include",
        "lib/third-party/glm/"
	}

    libdirs
    {
        "lib/third-party/SDL2-w64/lib/x64",
        "lib/third-party/glew-2.2.0/lib/Release/x64"
    }

	links
	{
        "glew32",
        "OpenGL32",
        "glu32",
        "SDL2main",
        "SDL2",
        "SDL2_image",
        "SDL2_ttf"
	}

	filter "system:windows"
        cppdialect "C++17"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "RQ_DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "RQ_RELEASE"
		runtime "Release"
		optimize "on"


project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "off"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "game/include/**.h",
        "game/src/**.cpp",
    }
    
    includedirs
    {
        "src",
        "include",
        "game/src",
        "game/include",
        "lib/third-party/SDL2-w64/include",
        "lib/third-party/glew-2.2.0/include",
        "lib/third-party/glm/"
    }
        
    links
    {
        "RQEngine"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
    
       
		prebuildcommands
        {
			("{COPY} bin/" .. outputdir .. "/RQEngine/RQEngine.lib bin/" .. outputdir .. "/Sandbox")
        }

    
    filter "configurations:Debug"
        defines "RQ_DEBUG"
        symbols "on"

		postbuildcommands
		{
			("{COPYDIR} lib/debug/  bin/" .. outputdir .. "/Sandbox/")

			-- TODO: add resources
			-- ("{COPY} res/  ../bin/" .. outputdir .. "/RQEngine/res"),
            -- ("{COPY} game/res/  ../bin/" .. outputdir .. "/RQEngine/res")
		}
    
    
    filter "configurations:Release"
        defines "RQ_RELEASE"
        optimize "on"

		postbuildcommands
		{
			("{COPY} lib/release/  /bin/" .. outputdir .. "/Sandbox")
		}