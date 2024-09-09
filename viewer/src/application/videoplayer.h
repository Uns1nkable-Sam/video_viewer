#pragma once

#include "ofMain.h"

namespace Elements {

class VideoPlayer
{
public:
    VideoPlayer(const std::string& video_file_path):
        m_video_file_path(video_file_path)
    {}

    void setup(const ofRectangle& rect);
    void draw();
    void update();

private:
    ofVideoPlayer m_video_player;
    ofRectangle m_video_rect;

    std::string m_video_file_path;
};

} // namespace Elements
