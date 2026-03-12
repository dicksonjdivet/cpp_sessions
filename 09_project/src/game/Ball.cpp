#include <game/Ball.h>

#include <engine/IRenderer.h>

static float x = 400;
static float y = 300;

void Ball::update()
{
    x += 1;
    y += 1;
}

void Ball::render(engine::IRenderer& renderer)
{
    renderer.drawCircle(x, y, 10, {255, 255, 255});
}
