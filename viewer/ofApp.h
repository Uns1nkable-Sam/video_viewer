#pragma once

#include "ofMain.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"
#include "server.h"



class ClientHandler : public CefClient, public CefRenderHandler {
public:
    ClientHandler(int width, int height);
    ~ClientHandler();

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override {
        return this;
    }

    virtual void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override;
    virtual void OnPaint(CefRefPtr<CefBrowser> browser,
                         CefRenderHandler::PaintElementType type,
                         const CefRenderHandler::RectList &dirtyRects,
                         const void *buffer,
                         int width, int height) override;

    unsigned char* getPixels();

    void createBrowser();
    void delayedBrowser();
private:
    int width, height;
    unsigned char* pixels;
    CefRefPtr<CefBrowser> browser;

    IMPLEMENT_REFCOUNTING(ClientHandler);
};

class ofApp : public ofBaseApp, public Web::IScreenshotMaker {
public:
    void setup();
    void update();
    void draw();
    void exit();
    void makeScreenshot();
    std::vector<unsigned char> getScreenshotData();
private:
    std::mutex draw_mutex;
    std::mutex screenshot_mutex;

    Web::Server m_server;

    ofTexture cefTexture;
    ClientHandler* clientHandler;
    ofVideoPlayer m_video_player;
    std::string m_video_file_path = "";

    uint64_t m_last_html_frame;
    uint64_t m_last_video_frame;

    uint64_t m_video_ms_per_frame = 40;
    uint64_t m_html_ms_per_frame = 20;

    ofImage screenShot;
    std::vector<unsigned char> m_image_bytes;
};
