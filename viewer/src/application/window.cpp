#include "window.h"

namespace Application {

void Window::setup() {
    // Set up the video and HTML areas
    int window_width = ofGetWidth();
    int window_height = ofGetHeight();

    // Set up video and HTML threads
    m_video_player.setup(ofRectangle(0, 0, window_width / 2, window_height));
    m_html_player.setup(ofRectangle(window_width / 2, 0, window_width / 2, window_height));

    // Start the threads
    m_video_player.startThread();
    m_html_player.startThread();
}

void Window::draw() {
    // Draw video and HTML content
    m_video_player.draw();
    m_html_player.draw();
}

void Window::exit() {
    // Stop the threads when exiting
    m_video_player.stopThread();
    m_html_player.stopThread();
}

} // namespace Application
