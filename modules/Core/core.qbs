import qbs.base 1.0

Product
{
    name: "Core"
    type: "dynamiclibrary"
    destination: "lib"

    Depends { name: "cpp" }

    files: [
        "src/String.cpp",
        "src/Exception.cpp",
        "src/Exceptions.cpp",
        "src/LogWriter.cpp",
        "src/Logger.cpp"
    ]
}
