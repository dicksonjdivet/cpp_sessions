#pragma once

namespace engine {

class Key {
public:
    enum class Code { ArrowUp, ArrowDown, KeyZ, KeyS };
    Code code;
};

}
