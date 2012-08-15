import qbs.base 1.0

Product
{
    name: "Core"
    type: "dynamiclibrary"
    destination: "lib"

    Depends { name: "cpp" }

    files: [
        "src/String.cpp"
    ]
}
