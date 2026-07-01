// FUNC_NAME: NPC::setActionState
// Address: 0x0084fae0
// Sets the NPC's action state to 5 (likely kActionState_Attack) and triggers the behavior's state change callback.

#include <cstdint>

class BaseBehavior {
public:
    virtual void onStateChange(); // vtable offset 0x10
};

class NPC {
private:
    int32_t m_actionState; // +0x84
    BaseBehavior* m_behavior; // +0x98

public:
    void setActionState(); // __thiscall
};

void NPC::setActionState() {
    m_actionState = 5; // Set state to 5 (e.g., kActionState_Attack)
    if (m_behavior != nullptr) {
        m_behavior->onStateChange(); // Notify behavior of state change via vtable
    }
}