// FUNC_NAME: ActionOptions::isActionActive

#include <cstdint>

class ActionOptions {
public:
    uint8_t m_state;        // +0x14: Current state/action identifier
    uint32_t m_actionBitmask; // +0x2c: Bitmask of active actions (bit per state)

    // Checks if the current action is considered "active" based on state.
    // For state 0x12 (18) always returns true.
    // For state 0x13 (19) returns true if the bitmask is non-zero.
    // For all other states checks bit (state & 0x1f) in the bitmask.
    bool isActionActive() const
    {
        if (m_state == 0x13) {
            return m_actionBitmask != 0;
        }
        if (m_state == 0x12) {
            return true;
        }
        return (m_actionBitmask & (1 << (m_state & 0x1f))) != 0;
    }
};