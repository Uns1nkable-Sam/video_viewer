#ifndef CEFHANDLER_H
#define CEFHANDLER_H

#include "include/cef_app.h"  // Include CEF headers (adjust path if necessary)
#include "include/cef_client.h"
#include "ofMain.h"

// CEF Handler Class (for Chromium)
class CEFHandler : public CefClient, public CefLifeSpanHandler, public CefRenderHandler {
public:
    CefRefPtr<CefBrowser> browser;
    ofRectangle htmlRect;

    void setup(const ofRectangle& rect, const std::string& url) {
//        htmlRect = rect;

//        CefWindowInfo window_info;
//        window_info.SetAsWindowless(0);  // Windowless (offscreen) rendering

//        CefBrowserSettings browser_settings;
//        CefRefPtr<CefClient> client(this);

//        CefBrowserHost::CreateBrowser(window_info, client, url, browser_settings, nullptr, nullptr);
    }

    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
//        this->browser = browser;
//        CefLifeSpanHandler::OnAfterCreated(browser);
    }

    void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override {
//        rect = CefRect(0, 0, htmlRect.width, htmlRect.height);  // Set the size of the HTML content
    }

    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) override {
//        ofPixels pixels;
//        pixels.setFromExternalPixels((unsigned char*)buffer, width, height, OF_PIXELS_RGBA);

//        ofTexture texture;
//        texture.allocate(pixels);
//        texture.loadData(pixels);  // Update the texture with the new data

//        // Draw this texture in OpenFrameworks' draw() method
    }

    IMPLEMENT_REFCOUNTING(CEFHandler);
};

#endif // CEFHANDLER_H
