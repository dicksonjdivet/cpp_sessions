#include <engine/RaylibRenderer.h>

#include <raylib.h>

namespace engine {

static ::Color toRaylibColor(Color color)
{
    return {color.r, color.g, color.b, color.a};
}

void RaylibRenderer::clear(Color color)
{
    ClearBackground(toRaylibColor(color));
}

void RaylibRenderer::init(
    int width,
    int height,
    const char* title)
{
    InitWindow(width, height, title);
    SetTargetFPS(60);
}

void RaylibRenderer::drawRectangle(
    float x,
    float y,
    float width,
    float height,
    Color color)
{
    DrawRectangle(x, y, width, height, toRaylibColor(color));
}

void RaylibRenderer::drawCircle(
    float x,
    float y,
    float radius,
    Color color)
{
    DrawCircle(x, y, radius, toRaylibColor(color));
}

void RaylibRenderer::drawText(
    const char* text,
    float x,
    float y,
    int fontSize,
    Color color)
{
    DrawText(text, x, y, fontSize, toRaylibColor(color));
}

void RaylibRenderer::beginDraw()
{
    BeginDrawing();
}

void RaylibRenderer::endDraw()
{
    EndDrawing();
}

bool RaylibRenderer::shouldClose()
{
    return WindowShouldClose();
}

}
