#include "ofApp.h"

#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback_forward.h"
#include "include/base/cef_bind.h"
#include "include/wrapper/cef_closure_task.h"

#include "include/base/cef_callback.h"
#include "include/cef_app.h"


ClientHandler::ClientHandler(int width, int height, const std::string& current_path) :
    width(width),
    height(height),
    m_current_path(current_path)
{
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

void ClientHandler::delayedBrowserCreation() {
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, base::BindOnce(&ClientHandler::createBrowser, base::Unretained(this)));
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
    CefBrowserHost::CreateBrowserSync(window_info, this, "file://"+m_current_path+"/ball.html", browser_settings, nullptr, nullptr);
}

void ofApp::setup() {
    m_current_path = std::filesystem::current_path();
    int frameRate = int(std::round(1000 / std::min(m_video_ms_per_frame, m_html_ms_per_frame)));
    ofSetFrameRate(frameRate);
    ofSetVerticalSync(true);

    CefSettings settings;
    CefString(&settings.cache_path) = m_current_path + "/cef_cache";
    settings.no_sandbox = true;
    settings.windowless_rendering_enabled = true;
    settings.command_line_args_disabled = true;
    settings.multi_threaded_message_loop = true;

    CefInitialize(CefMainArgs(), settings, nullptr, nullptr);

    CefBrowserSettings browser_settings;
    clientHandler = new ClientHandler(ofGetWidth() / 2, ofGetHeight(), m_current_path);


    clientHandler->delayedBrowserCreation();
    cefTexture.allocate(ofGetWidth() / 2, ofGetHeight(), GL_RGBA);

    if (!m_video_player.load(m_current_path + "/cat.mp4")){
        ofLogError() << "Failed to load video: " << m_video_file_path;
        exit();
    }

    m_last_html_frame = ofGetElapsedTimeMillis();
    m_last_video_frame = ofGetElapsedTimeMillis();

    m_video_player.setLoopState(OF_LOOP_NORMAL);
    m_video_player.setPaused(true);
    m_video_player.play();

    m_server.withScreenshotMaker(this).run();
}

void ofApp::update() {
    auto millis = ofGetElapsedTimeMillis();
    if(millis - m_last_video_frame_drawn >= m_video_ms_per_frame) {
        m_video_player.update();
        videoPixels = m_video_player.getPixels();
        image.setFromPixels(videoPixels);
        m_last_video_frame_drawn = millis;
    }
}

void ofApp::draw() {
    cefTexture.loadData(clientHandler->getPixels(), ofGetWidth() / 2, ofGetHeight(), GL_RGBA);
    cefTexture.draw(0, 0);

    image.draw(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());

    if (need_screenshot.load()) {
        ofBuffer buf;
        screenShot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        ofSaveImage(screenShot.getPixels(), buf, OF_IMAGE_FORMAT_PNG);
        std::lock_guard<std::mutex> guard(draw_mutex);
        m_image_bytes.resize(buf.size());
        memcpy(m_image_bytes.data(), buf.getData(), buf.size());
        need_screenshot.store(false);
        need_screenshot.notify_all();
    }
}

void ofApp::exit()
{
    m_server.stop();
}

std::vector<unsigned char> ofApp::makeScreenshot() {
    need_screenshot.store(true);
    need_screenshot.wait(true);
    std::lock_guard<std::mutex> guard(draw_mutex);
    return std::vector<unsigned char>(m_image_bytes);
}
