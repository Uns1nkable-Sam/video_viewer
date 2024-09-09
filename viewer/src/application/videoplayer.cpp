#include "videoplayer.h"

namespace Elements {

void VideoPlayer::setup(const ofRectangle& rect) {
    if (!m_video_player.load(m_video_file_path)){
            ofLogError() << "Failed to load video: " << m_video_file_path;
            return;
        }
    m_video_rect = rect;
    m_video_player.setLoopState(OF_LOOP_NORMAL);
    m_video_player.play();
    ofLogNotice() << "Video rect: " << m_video_rect;

}

void VideoPlayer::draw() {
    m_video_player.draw(m_video_rect);  // Draw the video
}

void VideoPlayer::update()
{
    int millis = ofGetElapsedTimeMillis();
    if (millis % 40 == 0) {
        m_video_player.update();  // Update the video
    }
}

} // namespace Elements
