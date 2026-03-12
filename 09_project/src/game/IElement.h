#pragma once

namespace engine {
class IRenderer;
}

class IElement {
public:
    virtual ~IElement() = default;

    virtual void update() = 0;

    virtual void render(engine::IRenderer& renderer) = 0;
};
