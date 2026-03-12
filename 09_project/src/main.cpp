#include <game/Game.h>

#include <engine/RaylibInputListener.h>
#include <engine/RaylibRenderer.h>

int main(
    int argc,
    char* argv[])
{
    Game game;
    engine::RaylibRenderer renderer;
    engine::RaylibInputListener listener;

    game.run(renderer, listener);

    return 0;
}
