 
#pragma once

#include "include/base/cef_callback_forward.h"
#include "ofMain.h"
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"



// Custom ClientHandler class
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

// OF App
class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofTexture cefTexture;
    ClientHandler* clientHandler;

    ofVideoPlayer m_video_player;

    std::string m_video_file_path = "";
    void createBrowser();
};
