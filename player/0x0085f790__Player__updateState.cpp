// FUNC_NAME: Player::updateState
// Address: 0x0085f790
// Role: Updates player state machine – handles state transitions, flags, and time‑based transform resets.

#include <cstdint>

// Called functions (renamed for clarity)
void applyStateBehavior();                          // FUN_0085f170
void releaseEntityHandle(uint32_t handle);          // FUN_00851210
void* getGameManager();                             // FUN_00471610 – returns something with a float at +0x34
void resetTransform(void* transformData);           // FUN_004088c0

extern float g_fTimeThreshold;                      // DAT_00e44744

class Player {
    // Layout (offsets from `this`):
    // +0x3c : Matrix44 m_transform;      // or similar transform data
    // +0xf28: uint32   m_stateFlags;
    // +0xf2c: int32    m_currentState;
    // +0xf94: uint32   m_entityHandle;

public:
    void updateState() {
        // Branch on lowest bit of stateFlags
        if (!(m_stateFlags & 0x1)) {
            // State flag clear: if state is 2, apply behavior
            if (m_currentState == 2) {
                applyStateBehavior();
            }
            // Set flag 0x20000 (e.g., "pending release" or "transition done")
            m_stateFlags |= 0x20000;
        } else {
            // State flag set: apply behavior and release the entity handle
            applyStateBehavior();
            releaseEntityHandle(m_entityHandle);
        }

        // Global game manager time check – if manager time <= threshold (and not equal),
        // reset the player's transform (e.g., snap to ground or re‑parent)
        void* manager = getGameManager();
        float managerTime = *(float*)((uint8_t*)manager + 0x34);
        if (managerTime <= g_fTimeThreshold && g_fTimeThreshold != managerTime) {
            resetTransform((uint8_t*)this + 0x3c);
        }
    }

private:
    // Actual member declarations omitted – offsets are used directly.
    // The class layout is large (size > 0xF28).
};