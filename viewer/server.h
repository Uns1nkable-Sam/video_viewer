#pragma once

#include <memory>
#include <thread>
#include <vector>

#include "crow.h"

namespace Web {

class IScreenshotMaker {
public:
    virtual std::vector<unsigned char> makeScreenshot() = 0;
};

class Server
{
public:
    Server(int port = 18008):
        m_port(port)
    {}

    Server& withScreenshotMaker(IScreenshotMaker* maker);

    void run();
    void stop();
protected:
    virtual void init();
private:
    std::shared_ptr<std::thread> m_server_thread;
    bool m_need_to_stop = false;

    int m_port;
    crow::SimpleApp m_crow;

    IScreenshotMaker* m_screenshots;
};

} // namespace Web

