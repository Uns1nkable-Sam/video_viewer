#include "htmlplayer.h"

namespace Elements {

void HTMLPlayer::setup(const ofRectangle& rect) {
    m_html_rect = rect;
    m_html_player.setup(rect, m_html_file_path);
}

void HTMLPlayer::update()
{

}

void HTMLPlayer::draw() {

}

} // namespace Elements
