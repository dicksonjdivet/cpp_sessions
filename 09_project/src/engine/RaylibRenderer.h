#pragma once

#include <engine/IRenderer.h>

namespace engine {

class RaylibRenderer : public IRenderer {
public:
    void clear(Color color) override;

    void init(
        int width,
        int height,
        const char* title) override;

    bool shouldClose() override;

    void beginDraw() override;

    void endDraw() override;

    void drawRectangle(
        float x,
        float y,
        float width,
        float height,
        Color color) override;

    void drawCircle(
        float x,
        float y,
        float radius,
        Color color) override;

    void drawText(
        const char* text,
        float x,
        float y,
        int fontSize,
        Color color) override;
};

}
