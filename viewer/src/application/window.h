#pragma once

#include <memory>

#include "ofMain.h"

namespace Application {

class Window: public ofBaseApp
{
public:
    explicit Window();
};

typedef std::shared_ptr<Window> WindowPtr;

} // namespace Application

