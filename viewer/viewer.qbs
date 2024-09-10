import qbs
import qbs.FileInfo
import "/home/raistlin/software/of_v0.12.0_linux64gcc6_release/libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as OfApp


Project {
    id: project
//    property string ofRoot: qbs.getEnv("OF_ROOT")
    property string of_root: "/home/raistlin/software/of_v0.12.0_linux64gcc6_release"
    property string cef_root: "/home/raistlin/software/cef_binary_128.4.9+g9840ad9+chromium-128.0.6613.120_linux64"
    property string crow_root: "/home/raistlin/software/Crow"

    references: [
        FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs"),
    ]

    OfApp {
        name: { return FileInfo.baseName(sourceDirectory) }
        cpp.cxxLanguageVersion: "c++20"
        files: [
            "main.cpp",
            "ofApp.cpp",
            "ofApp.h",
            "server.cpp",
            "server.h",
        ]

        of.addons: [
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: [
           project.cef_root,
           FileInfo.joinPaths(crow_root, "/include"),
        ]     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
                                // and can be checked with #ifdef or #if in the code
        cpp.libraryPaths: [
            FileInfo.joinPaths(cef_root, "/Release"),
            FileInfo.joinPaths(cef_root, "/build/libcef_dll_wrapper")
        ]
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.dynamicLibraries: ["cef", "GLESv2"] // dynamic libraries
        of.staticLibraries: ["cef_dll_wrapper"]

        Depends {
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        Depends{
            name: "openFrameworks"
        }

        Group {
            name: "Copy after build"
            files: [
                "resources/*",
            ]
            fileTags: ["install"]

            qbs.install: true
            qbs.installDir: "bin"
        }
        Group {
            name: "The App itself"
            fileTagsFilter: "application"
            fileTags: ["install"]
            qbs.install: true
            qbs.installDir: "bin"
        }
    }

    property bool makeOF: true
    property bool precompileOfMain: false


}
