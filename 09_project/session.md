# Project Pong

In this session, we will create a simple Pong game using C++ and the Raylib library. We will set up our project structure, configure CMake to include Raylib, and implement the game logic.

The goal of this session is to demonstrate how to structure a C++ project, use CMake for build configuration, and implement a simple game using Raylib.

:::mermaid
classDiagram
    direction LR

    class IElement {
        <<interface>>
    }

    class Ball
    class Paddle
    class Score
    class Separator

    class Game {
        -mBall : Ball
        -mLeftPaddle : Paddle
        -mRightPaddle : Paddle
        -mLeftScore : Score
        -mRightScore : Score
        -mSeparator : Separator
    }

    class IRenderer {
        <<interface>>
    }

    class IInputListener {
        <<interface>>
    }

    class RaylibRenderer
    class RaylibInputListener

    Ball ..|> IElement
    Paddle ..|> IElement
    Score ..|> IElement
    Separator ..|> IElement

    Game *-- Ball
    Game *-- "2" Paddle
    Game *-- "2" Score
    Game *-- Separator

    RaylibRenderer ..|> IRenderer
    RaylibInputListener ..|> IInputListener

    Game --> IRenderer : injected
    Game --> IInputListener : injected

:::

Bonus:
- Implement a simple AI for the right paddle that follows the ball's vertical position.
- Add sound effects for when the ball hits the paddles or scores a point.
- Implement bonuses that randomly appear on the field, such as speed boosts, ball making sinuous movements, or enlarging the paddle for a short duration.