import qbs.base 1.0

Product
{
    name: "StdWriter"
    type: "dynamiclibrary"
    destination: "lib/plugins"

    Depends { name: "cpp" }
    Depends { name: "Core" }

    cpp.rpaths: [
        "../../../../build/debug/lib",
        "../../../../build/release/lib"
    ]
    cpp.libraryPaths: [
        "../../../../build/debug/lib",
        "../../../../build/release/lib"
    ]
    cpp.includePaths: [ '../../src']
    cpp.dynamicLibraries: ['Core']

    files: [
        "../../src/services/logger/plugins/StdLogger/StdWriter.cpp",
    ]
}
