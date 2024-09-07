#include "htmlplayer.h"

namespace Elements {

void HTMLPlayer::setup(const ofRectangle& rect) {
    m_html_player.loadURL(m_html_file_path);
    m_html_rect = rect;
}

void HTMLPlayer::threadedFunction() {
    while (isThreadRunning()) {
        if (lock()) {
            m_html_player.update();  // Update the video
            unlock();
        }
        sleep(20);  // Control frame rate (~50 FPS)
    }
}

void HTMLPlayer::draw() {
    if (lock()) {
        m_html_player.draw(m_html_rect);  // Draw the video
        unlock();
    }
}

} // namespace Elements
