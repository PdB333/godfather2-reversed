// FUNC_NAME: PlayerSM::setActive

// Address: 0x00566c40
// Role: Sets the active state of a player state machine.
// When active==false, resets state to idle (0), substate to 2, and clears flag bit 2.
// When active==true, transitions to state 1 unless already in state 8 (terminal?).
// After state change, calls a virtual method on the target object (vtable offset 0x44).

#include <cstdint>

class PlayerSM {
public:
    void setActive(bool active);

private:
    // Offsets into this object (x86, no padding assumptions unless noted)
    // +0x00: vtable pointer
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: m_pTarget (pointer to a separate object with a vtable, e.g. owner/controller)
    // +0x10: m_state (uint32_t)
    // +0x14: m_substate (uint8_t)
    // +0x2C: m_flags (uint32_t)

    // Intermediate fields omitted for brevity
};

void __thiscall PlayerSM::setActive(bool active) {
    if (!active) {
        // Deactivating – reset to idle state, substate 2, clear pending flag (bit 2)
        this->m_substate = 2;
        this->m_state = 0;
        this->m_flags &= ~0x4;   // 0xfffffffb mask
    } else if (this->m_state != 8) {
        // Activating – set state to active (1) unless already in a locked/terminal state
        this->m_state = 1;
    }

    // Notify the target object via its vtable (function at offset 0x44)
    if (this->m_pTarget != nullptr) {
        void (**vtable)(void) = *reinterpret_cast<void(***)(void)>(this->m_pTarget);
        vtable[17]();   // 0x44 / 4 = 17
    }
}