#pragma once

#include <game/IElement.h>

class Ball : public IElement {
public:
    void update() override;

    void render(engine::IRenderer& renderer) override;
};
