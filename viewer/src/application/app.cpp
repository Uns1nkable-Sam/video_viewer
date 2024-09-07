#include "app.h"

#include "ofMain.h"

namespace Application {

App::App()
{
}

int App::run()
{
    createWindow();
    ofRunApp(m_of_window, m_window);
    ofRunMainLoop();
    return 0;
}

void App::createWindow()
{
    ofGLWindowSettings settings;
    settings.setSize(300, 300);
    settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

    m_of_window = ofCreateWindow(settings);
    m_window = make_shared<Application::Window>();
}

} // namespace Application
