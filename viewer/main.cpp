#include <iostream>

#include "app.h"

using namespace std;

int main(int argc, char *argv[])
{
    CefMainArgs main_args(argc, argv);
    CefRefPtr<CefApp> cef_app;
    int exit_code = CefExecuteProcess(main_args, cef_app.get(), nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }

    cout << "Hello World!" << endl;
    Application::App app;
    int result = app.run(argc, argv);

    return result;
}
