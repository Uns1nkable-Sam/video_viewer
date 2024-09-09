#pragma once

#include "ofMain.h"
#include "cefhandler.h"

namespace Elements {

class HTMLPlayer
{
public:
    HTMLPlayer(const std::string& html_file_path):
        m_html_file_path(html_file_path)
    {}

    void setup(const ofRectangle& rect);
    void update();
    void draw();

private:
    CEFHandler m_html_player;
    ofRectangle m_html_rect;

    std::string m_html_file_path;
};

} // namespace Elements
