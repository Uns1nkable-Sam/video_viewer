#include "ofMain.h"
#include "ofApp.h"

// Main entry point for OpenFrameworks app
int main(int argc, char** argv) {
    CefMainArgs main_args(argc, argv);
    CefRefPtr<CefApp> cef_app;
    int exit_code = CefExecuteProcess(main_args, cef_app.get(), nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }

    ofSetupOpenGL(1024, 768, OF_WINDOW); // setup the GL context
    ofRunApp(new ofApp()); // start the app
    CefShutdown();
}
