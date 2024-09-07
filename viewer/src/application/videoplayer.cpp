#include "videoplayer.h"

namespace Elements {

void VideoPlayer::setup(const ofRectangle& rect) {
    m_video_player.load(m_video_file_path);
    m_video_player.setLoopState(OF_LOOP_NORMAL);
    m_video_player.play();
    m_video_rect = rect;
}

void VideoPlayer::threadedFunction() {
    while (isThreadRunning()) {
        if (lock()) {
            m_video_player.update();  // Update the video
            unlock();
        }
        sleep(20);  // Control frame rate (~50 FPS)
    }
}

void VideoPlayer::draw() {
    if (lock()) {
        m_video_player.draw(m_video_rect);  // Draw the video
        unlock();
    }
}

} // namespace Elements
