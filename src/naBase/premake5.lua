project "naBase"
    language "C++"
    kind "StaticLib"
    includedirs {".."}

    files {
        "**.cpp",
        "**.h"
    }

