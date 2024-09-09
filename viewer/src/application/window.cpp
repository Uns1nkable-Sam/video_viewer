#include "window.h"

namespace Application {

void Window::setup() {
    int window_width = ofGetWidth();
    int window_height = ofGetHeight();
    ofResetElapsedTimeCounter();
    m_video_player.setup(ofRectangle(0, 0, window_width / 2, window_height));
//    m_html_player.setup(ofRectangle(window_width / 2, 0, window_width / 2, window_height));
}

void Window::update()
{
    m_video_player.update();
//    m_html_player.update();
}

void Window::draw() {
    m_video_player.draw();
//    m_html_player.draw();
}

void Window::exit() {

}

} // namespace Application
