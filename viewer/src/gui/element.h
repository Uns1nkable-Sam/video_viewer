#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <vector>



namespace GUI {

typedef int Color;

class Point
{
public:
    Point(const int x=0, const int y=0): m_x(x), m_y(y) {}
    Point(Point &other) = default;
    Point(Point &&other) = default;
    int x() const;
    int y() const;

private:
    int m_x;
    int m_y;
};

class Source{

};

class Element
{
public:
    Element();
    Element(Element &&other) = default;
    Element& with_coordinates(const Point& point);
    Element& with_size(const Point& point);
    Element& with_children(const std::vector<Element>& children);
private:
    Point m_coordinates;
    Point m_size;
    std::vector<Element>& m_children;
};

class Panel:public Element
{
public:
    Panel();
    Panel(Panel &&other) = default;
    Panel& with_color(const Color& color);
    Panel& with_source(const Source& source);
private:
    Color m_color;
    Source m_source;
};

} // namespace GUI

#endif // GUI_ELEMENT_H
