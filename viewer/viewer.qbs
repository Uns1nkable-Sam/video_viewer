import qbs
import qbs.FileInfo
import "/home/raistlin/software/of_v0.12.0_linux64gcc6_release/libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as OfApp


Project {
    id: project
//    property string ofRoot: qbs.getEnv("OF_ROOT")
    property string of_root: "/home/raistlin/software/of_v0.12.0_linux64gcc6_release"

    references: [
        FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")
    ]

    OfApp {
        name: { return FileInfo.baseName(sourceDirectory) }
        cpp.cxxLanguageVersion: "c++17"

        files: [
            "main.cpp",
            "src/application/app.cpp",
            "src/application/app.h",
//            "src/application/htmlplayer.cpp",
//            "src/application/htmlplayer.h",
            "src/application/videoplayer.cpp",
            "src/application/videoplayer.h",
            "src/application/window.cpp",
            "src/application/window.h",
        ]

        of.addons: [
        ]


        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
                                // and can be checked with #ifdef or #if in the code
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.staticLibraries: []  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        Depends {
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }

    }
    property bool makeOF: true
    property bool precompileOfMain: false


}
