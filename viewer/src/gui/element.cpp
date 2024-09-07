#include "element.h"

namespace GUI {

Element::Element()
{

}

Element &Element::with_size(const Point &size)
{
    m_size = size;

}

Element &Element::with_children(const std::vector<Element> &children)
{
    m_children = children;
    return *this;
}


} // namespace GUI
