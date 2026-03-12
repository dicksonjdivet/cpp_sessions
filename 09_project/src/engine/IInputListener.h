#pragma once

#include <engine/Key.h>

namespace engine {

class IInputListener {
public:
    virtual ~IInputListener() = default;

    virtual bool isKeyPressed(Key key) = 0;
    virtual bool isKeyReleased(Key key) = 0;
};

}
