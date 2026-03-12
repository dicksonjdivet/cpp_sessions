#include <engine/RaylibInputListener.h>

#include <raylib.h>

namespace engine {

static int toRaylibKey(Key key)
{
    switch (key.code) {
    case Key::Code::ArrowUp:
        return 265;
    case Key::Code::ArrowDown:
        return 264;
    case Key::Code::KeyZ:
        return 90;
    case Key::Code::KeyS:
        return 83;
    }

    return 0;
}

bool RaylibInputListener::isKeyPressed(Key key)
{
    return IsKeyPressed(toRaylibKey(key));
}

bool RaylibInputListener::isKeyReleased(Key key)
{
    return IsKeyReleased(toRaylibKey(key));
}

}
