#pragma once

#include "ofMain.h"
#include "window.h"

namespace Application {

class App : public ofBaseApp
{
public:
    App();
    int run(int argc, char *argv[]);
private:
    void runCef(int argc, char *argv[]);
    void runOf();
    void stop();
    void createWindow();
    bool updateCef(ofEventArgs &args);
    Application::WindowPtr m_window;
    std::shared_ptr<ofAppBaseWindow> m_of_window;
    std::shared_ptr<std::thread> cef_thread;
    std::shared_ptr<std::thread> of_thread;
    bool shutdown_requested = false;
    bool cef_is_running = false;
};

} // namespace Application
