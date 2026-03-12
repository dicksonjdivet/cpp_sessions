#include <game/Game.h>

#include <engine/IRenderer.h>

Game::Game()
    : mBall()
    , mLeftPaddle()
    , mRightPaddle()
    , mLeftScore()
    , mRightScore()
    , mSeparator()
{
    mElements.push_back(&mBall);
}

// Main game loop
void Game::run(
    engine::IRenderer& renderer,
    engine::IInputListener& inputListener)
{
    renderer.init(800, 600, "Pong");

    while (!renderer.shouldClose()) {
        processInput(inputListener);
        update();
        render(renderer);
    }
}

// Process user input here, such as moving the paddles based on key presses
void Game::processInput(engine::IInputListener& inputListener)
{
}

// Do all the game logic here, such as moving the ball and checking for collisions
void Game::update()
{
    mBall.update();
}

// Render all game elements here, such as the ball, paddles, scores, and separator
void Game::render(engine::IRenderer& renderer)
{
    renderer.beginDraw();
    renderer.clear({0, 0, 0});

    for (auto element : mElements) {
        element->render(renderer);
    }

    renderer.endDraw();
}
