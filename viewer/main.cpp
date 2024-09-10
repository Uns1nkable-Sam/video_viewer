#include "include/cef_app.h"
#include "ofApp.h"

int main(int argc, char** argv) {
    CefMainArgs main_args(argc, argv);
    CefRefPtr<CefApp> cef_app;
    int exit_code = CefExecuteProcess(main_args, cef_app.get(), nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }


    ofSetupOpenGL(1024, 768, OF_WINDOW);
    ofRunApp(new ofApp());
    CefShutdown();
}
