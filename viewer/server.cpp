#include "server.h"

namespace Web {

Server &Server::withScreenshotMaker(IScreenshotMaker *maker)
{
    m_screenshots = maker;
    return *this;
}

void Server::init()
{
    if (m_screenshots) {
        CROW_ROUTE(m_crow, "/screenshot.png")([&](){
            m_screenshots->makeScreenshot();
            auto data = m_screenshots->getScreenshotData();
            return crow::response(200, "image/png", std::string(data.begin(), data.end()));
        });
    }
    CROW_ROUTE(m_crow, "/health")([](){
        return crow::json::wvalue({{"status", "OK"}});
    });
}

void Server::run()
{
    if (m_server_thread) {
        return;
    }
    m_need_to_stop = false;
    m_server_thread = std::make_shared<std::thread>(std::thread([&](){
        init();
        m_crow.port(m_port).multithreaded().run();
    }));
    m_server_thread->detach();
}

void Server::stop()
{
    m_crow.stop();
    if (m_server_thread->joinable())
        m_server_thread->join();
}

} // namespace Web
