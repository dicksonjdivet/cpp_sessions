#pragma once

#include <cstdint>

namespace engine {

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a {255};
};

}
