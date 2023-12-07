project "Day3"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "**.h",
        "**.cpp",
    }