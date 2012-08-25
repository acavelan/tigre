import qbs.base 1.0

Product
{
    name: "Core"
    type: "dynamiclibrary"
    destination: "lib"

    Depends { name: "cpp" }

    Properties
    {
        condition: qbs.targetOS == "linux"
        cpp.dynamicLibraries: ['dl']
    }

    files: [
        "../src/String.cpp",
        "../src/Exception.cpp",
        "../src/Exceptions.cpp",
        "../src/SharedLibrary.cpp",
    ]
}
