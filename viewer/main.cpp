#include "include/cef_app.h"
#include "ofApp.h"

int main(int argc, char** argv) {
    CefMainArgs main_args(argc, argv);
    CefRefPtr<CefApp> cef_app;
    int exit_code = CefExecuteProcess(main_args, cef_app.get(), nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }

    // Set up window settings
    ofGLFWWindowSettings settings;
    settings.setSize(1024, 768);  // Set the window size
    settings.resizable = false;   // Disable window resizing

    // Create the window with these settings
    ofCreateWindow(settings);

    ofRunApp(new ofApp());
    CefShutdown();
}
