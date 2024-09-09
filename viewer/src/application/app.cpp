#include "app.h"

#include "ofMain.h"

namespace Application {

App::App()
{
}

int App::run(int argc, char *argv[])
{
    runCef(argc, argv);
    while (!cef_is_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Add a small sleep to avoid busy waiting
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Add a small sleep to avoid busy waiting
    runOf();
    //cef_thread->join();
    stop();
    return 0;
}

void App::runCef(int argc, char *argv[])
{
    cef_thread = make_shared<std::thread>([&]() {
        CefMainArgs main_args(argc, argv);
        CefSettings settings;
        CefString(&settings.cache_path) = "/home/raistlin/work/boilerplates/video_viewer/viewer/bin/cef_cache";
        settings.no_sandbox = true;
        settings.windowless_rendering_enabled = true;
        settings.command_line_args_disabled = true;
        CefInitialize(main_args, settings, nullptr, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Add a small sleep to avoid busy waiting
        cef_is_running = true;
        while (!shutdown_requested) {
            CefDoMessageLoopWork();  // Handle CEF events in this thread
            std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Add a small sleep to avoid busy waiting
        }
        CefShutdown();
    });
    cef_thread->detach();
}


void App::runOf()
{
//    of_thread = make_shared<std::thread>([&](){
        createWindow();
//        ofAddListener(ofEvents().update, this, &App::updateCef);
        ofRunApp(m_of_window, m_window);
        ofRunMainLoop();
//    });
//    of_thread->join();
}

void App::stop()
{
    shutdown_requested = true;
    if (cef_thread && cef_thread->joinable()) {
        cef_thread->join();
    }
}

void App::createWindow()
{
    ofGLWindowSettings settings;
    settings.setSize(1024, 768);
    settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

    m_of_window = ofCreateWindow(settings);
    m_window = make_shared<Application::Window>("/home/raistlin/software/of_v0.12.0_linux64gcc6_release/examples/video/videoPlayerExample/bin/data/movies/fingers.mp4",
                                                "file:///home/raistlin/work/boilerplates/video_viewer/viewer/bin/ball.html");
}

bool App::updateCef(ofEventArgs &args)
{
//    if (cef_thread) {
//        CefDoMessageLoopWork();
//    }
    return true;
}

} // namespace Application
