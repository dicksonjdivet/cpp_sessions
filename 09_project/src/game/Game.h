#pragma once

#include <game/Ball.h>
#include <game/Paddle.h>
#include <game/Score.h>
#include <game/Separator.h>

#include <vector>

namespace engine {
class IInputListener;
class IRenderer;
}

class Game {
public:
    Game();
    void run(
        engine::IRenderer& renderer,
        engine::IInputListener& inputListener);

private:
    void render(engine::IRenderer& renderer);
    void processInput(engine::IInputListener& inputListener);
    void update();

    Ball mBall;
    Paddle mLeftPaddle;
    Paddle mRightPaddle;
    Score mLeftScore;
    Score mRightScore;
    Separator mSeparator;
    std::vector<IElement*> mElements; // Use a vector to store pointers to all game elements for easy rendering and updating
};
