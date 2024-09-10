#include "ofApp.h"

#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback_forward.h"
#include "include/base/cef_bind.h"
#include "include/wrapper/cef_closure_task.h"

#include "include/base/cef_callback.h"
#include "include/cef_app.h"


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

    CefBrowserSettings browser_settings;
    browser_settings.windowless_frame_rate = 50;
    CefBrowserHost::CreateBrowserSync(window_info, this, "file:///home/raistlin/work/boilerplates/cef_of_example/bin/ball.html", browser_settings, nullptr, nullptr);
}

void ofApp::setup() {
    int frameRate = int(std::round(1000 / std::min(m_video_ms_per_frame, m_html_ms_per_frame)));
    ofSetFrameRate(frameRate);
    ofSetVerticalSync(true);

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

    m_last_html_frame = ofGetElapsedTimeMillis();
    m_last_video_frame = ofGetElapsedTimeMillis();

    m_video_player.setLoopState(OF_LOOP_NORMAL);
    m_video_player.setPaused(true);

    m_server.withScreenshotMaker(this).run();
}

void ofApp::update() {
    auto millis = ofGetElapsedTimeMillis();
    auto diff = millis - m_last_video_frame;

    int next_frame = m_video_player.getCurrentFrame() + int(std::ceil(diff / m_video_ms_per_frame));
    if (next_frame >= m_video_player.getTotalNumFrames()) {
        next_frame = next_frame % m_video_player.getTotalNumFrames();
    }

    if(next_frame != m_video_player.getCurrentFrame()) {
//        ofLogNotice() << "current_frame: " << next_frame;
        m_video_player.setFrame(next_frame);
        m_video_player.update();
        m_last_video_frame = millis;
    }

    if (diff > m_video_ms_per_frame) {
        ofLogNotice() << diff;
    }
}

void ofApp::draw() {
    std::lock_guard<std::mutex> guard(draw_mutex);
    ofBackground(100, 100, 100);
    cefTexture.loadData(clientHandler->getPixels(), ofGetWidth() / 2, ofGetHeight(), GL_RGBA);
    cefTexture.draw(0, 0);
    m_video_player.draw(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());
}

void ofApp::exit()
{
    m_server.stop();
}

void ofApp::makeScreenshot() {
    ofBuffer buf;
    {
        std::lock_guard<std::mutex> guard(draw_mutex);
        screenShot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        ofSaveImage(screenShot.getPixels(), buf, OF_IMAGE_FORMAT_PNG);
        m_image_bytes.resize(buf.size());
    }
    {
        std::lock_guard<std::mutex> guard(screenshot_mutex);
        memcpy(m_image_bytes.data(), buf.getData(), buf.size());
    }
}

std::vector<unsigned char> ofApp::getScreenshotData() {
    std::lock_guard<std::mutex> guard(screenshot_mutex);
    return std::move(std::vector<unsigned char>(m_image_bytes));
}
