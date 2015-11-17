-- premake5.lua
workspace "Natural"
    configurations { "Debug", "Release" }
    includedirs "3rdparty"
    include "./src/naBase"

newaction {
    trigger    = "clean",
    description = "Remove all binaries and generated files",
    execute = function()
        os.remove("Natural.sdf")
        os.remove("Natural.sln")
        os.remove("Natural.v11.suo")
        os.remove("naBase.vcxproj")
        os.rmdir("obj")
        os.rmdir("bin")
    end
}
