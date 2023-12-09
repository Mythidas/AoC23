workspace "AoC23"
    architecture "x64"
    startproject "Day1"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Day1"
include "Day2"
include "Day3"
include "Day4"
include "Day5"