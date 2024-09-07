#pragma once

#include "ofMain.h"
#include "window.h"

namespace Application {

class App : public ofBaseApp
{
public:
    App();
    int run();
private:
    void createWindow();
    Application::WindowPtr m_window;
    std::shared_ptr<ofAppBaseWindow> m_of_window;
};

} // namespace Application
