#pragma once

#include <memory>

#include "ofMain.h"

#include "htmlplayer.h"
#include "videoplayer.h"

namespace Application {

class Window: public ofBaseApp
{
public:
    explicit Window(const std::string& video_file_path, const std::string& html_file_path):
        m_video_file_path(video_file_path),
        m_html_file_path(html_file_path),
        m_video_player(video_file_path),
        m_html_player(html_file_path)
    {}

    void setup();
    void draw();
    void exit();

private:
    Elements::VideoPlayer m_video_player;
    Elements::HTMLPlayer m_html_player;

    std::string m_html_file_path;
    std::string m_video_file_path;
};

typedef std::shared_ptr<Window> WindowPtr;

} // namespace Application

