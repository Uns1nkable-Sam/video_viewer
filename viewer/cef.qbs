import qbs
import qbs.FileInfo

Product {
    Depends { name: "cpp" }
    property string root: "CEF path was not set"
    type: "staticlibrary"
    qbsSearchPaths: "."
    cpp.includePaths: FileInfo.joinPaths(root, "/include")
    cpp.libraryPaths: FileInfo.joinPaths(root, "/Release")
    cpp.staticLibraries: ["libcef"]

    Probe {
        id: core_source
        property stringList files
        property stringList FILES_EXCLUDE: parent.FILES_EXCLUDE
        configure: {
            var source = Helpers.findSourceRecursive(FileInfo.joinPaths(root, '/libs/openFrameworks'));
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
        }
    }

    files: core_source.files
}
