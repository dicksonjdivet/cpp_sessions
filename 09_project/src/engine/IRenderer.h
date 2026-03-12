#pragma once

#include <engine/Color.h>

namespace engine {

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void clear(Color color) = 0;

    virtual void init(
        int width,
        int height,
        const char* title) = 0;

    virtual bool shouldClose() = 0;

    virtual void beginDraw() = 0;

    virtual void endDraw() = 0;

    virtual void drawRectangle(
        float x,
        float y,
        float width,
        float height,
        Color color) = 0;

    virtual void drawCircle(
        float x,
        float y,
        float radius,
        Color color) = 0;

    virtual void drawText(
        const char* text,
        float x,
        float y,
        int fontSize,
        Color color) = 0;
};

}
