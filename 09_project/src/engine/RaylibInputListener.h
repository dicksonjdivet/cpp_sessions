#include <engine/IInputListener.h>

namespace engine {

class RaylibInputListener : public IInputListener {
public:
    bool isKeyPressed(Key key) override;
    bool isKeyReleased(Key key) override;
};

}
