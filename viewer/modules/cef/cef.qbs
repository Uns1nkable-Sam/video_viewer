import qbs
import qbs.FileInfo
import "helpers.js" as Helpers

Product {
    id: cef_module
    name: "cef"
    type: "dynamiclibrary"
    qbsSearchPaths: "."

    property string root: "CEF path was not set"
    property string includePath: FileInfo.joinPaths(root, "/include")

    Depends { name: "cpp" }

    cpp.includePaths: includePath
    cpp.libraryPaths: FileInfo.joinPaths(root, "/Release")
    cpp.dynamicLibraries: ["libcef"]

    Probe {
        id: core_source
        property stringList files
        property stringList FILES_EXCLUDE: parent.FILES_EXCLUDE
        configure: {
            console.log("Looking in "+cef_module.includePath)
            var source = Helpers.findSourceRecursive(cef_module.includePath);
            var filteredSource = source.filter(function filterExcludes(path){
                for(exclude in FILES_EXCLUDE){
                    var patt = new RegExp(FILES_EXCLUDE[exclude]);
                    var match = patt.exec(path);
                    if(match!=null){
                        return false;
                    }
                }
                return true;
            });
            files = filteredSource;
            found = true;
            console.log("Files are "+files)
        }
    }

    files: core_source.files
}
