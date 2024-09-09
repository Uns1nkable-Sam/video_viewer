#include "ofApp.h"

#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback_forward.h"
#include "include/base/cef_bind.h"
#include "include/wrapper/cef_closure_task.h"

#include "include/base/cef_callback.h"
#include "include/cef_app.h"
#include "include/cef_parser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"


ClientHandler::ClientHandler(int width, int height) : width(width), height(height) {
    pixels = new unsigned char[width * height * 4]; // RGBA
}

ClientHandler::~ClientHandler() {
    delete[] pixels;
}

void ClientHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
    rect = CefRect(0, 0, width, height);
}

void ClientHandler::OnPaint(CefRefPtr<CefBrowser> browser,
                            CefRenderHandler::PaintElementType type,
                            const CefRenderHandler::RectList &dirtyRects,
                            const void* buffer, int width, int height) {
    memcpy(pixels, buffer, width * height * 4); // Copy pixels from CEF
}

void ClientHandler::delayedBrowser() {
    if (!CefCurrentlyOn(TID_UI)) {
        // Execute on the UI thread.
        CefPostTask(TID_UI, base::BindOnce(&ClientHandler::createBrowser, base::Unretained(this)));
        return;
    }
}

unsigned char* ClientHandler::getPixels() {
    return pixels;
}

void ClientHandler::createBrowser() {
    CEF_REQUIRE_UI_THREAD();

    CefWindowInfo window_info;
    window_info.SetAsWindowless(0);

    // Browser settings
    CefBrowserSettings browser_settings;

    // Create the browser instance
    CefBrowserHost::CreateBrowserSync(window_info, this, "file:///home/raistlin/work/boilerplates/cef_of_example/bin/ball.html", browser_settings, nullptr, nullptr);
}

void ofApp::setup() {
    // Setup CEF
    CefSettings settings;
    CefString(&settings.cache_path) = "/home/raistlin/work/boilerplates/video_viewer/viewer/bin/cef_cache";
    settings.no_sandbox = true;
    settings.windowless_rendering_enabled = true;
    settings.command_line_args_disabled = true;
    settings.multi_threaded_message_loop = true;

    CefInitialize(CefMainArgs(), settings, nullptr, nullptr);

    CefBrowserSettings browser_settings;
    clientHandler = new ClientHandler(ofGetWidth() / 2, ofGetHeight());


    clientHandler->delayedBrowser();
    cefTexture.allocate(ofGetWidth() / 2, ofGetHeight(), GL_RGBA);

    if (!m_video_player.load("/home/raistlin/work/boilerplates/cef_of_example/bin/fingers.mp4")){
        ofLogError() << "Failed to load video: " << m_video_file_path;
        return;
    }

    m_video_player.setLoopState(OF_LOOP_NORMAL);
    m_video_player.play();
}

void ofApp::update() {
    m_video_player.update();
}

void ofApp::draw() {
    cefTexture.loadData(clientHandler->getPixels(), ofGetWidth() / 2, ofGetHeight(), GL_RGBA);
    cefTexture.draw(0, 0);
    m_video_player.draw(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());  // Draw the video
}
