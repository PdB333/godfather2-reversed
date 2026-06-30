// FUNC_NAME: ControllerSlot::updateLastInputTime
// Address: 0x0068ca30
// Role: Checks if any input (buttons or analog sticks) is active on the controller slot
// and updates the last input timestamp accordingly.

#include <cstdint>

// Forward-declared external functions and globals.
struct ControllerState;
extern ControllerState* __fastcall getControllerState(uint8_t slotIndex); // 0x00410540

// Global input manager globals (singleton at 0x01223464)
extern struct InputManagerGlobals* g_inputManagerGlobals; // 0x01223464

// Global tick / current time (0x01205210)
extern uint32_t g_currentTime;

// Per-slot controller state structure
class ControllerSlot {
public:
    uint8_t  m_slotIndex;          // +0x14
    uint32_t m_lastInputTime;      // +0x30

    void updateLastInputTime();
};

// Controller state structure returned by getControllerState
struct ControllerState {
    float    leftStickX;   // +0x00
    float    leftStickY;   // +0x04
    float    rightStickX;  // +0x08
    float    rightStickY;  // +0x0C
    uint32_t buttons;      // +0x10
    char     connected;    // +0x3E (non‑zero if connected)
};

// Input manager globals containing the analog dead zone
struct InputManagerGlobals {
    char _pad[0x1694];
    float m_deadZoneSquared; // +0x1694
};

void ControllerSlot::updateLastInputTime() {
    // Only process slots 0–15
    if (m_slotIndex >= 16) {
        return;
    }

    // Square the dead‑zone threshold (already stored squared? The original code squares it again)
    float deadZone = g_inputManagerGlobals->m_deadZoneSquared;
    float deadZoneSquared = deadZone * deadZone;

    ControllerState* state = getControllerState(m_slotIndex);
    if (state != nullptr && state->connected != 0) {
        bool inputActive = false;

        // Check if any button in the lower 14 bits is pressed
        if ((state->buttons & 0x3FFF) != 0) {
            inputActive = true;
        } else {
            // Check left stick magnitude
            float leftMagSq = state->leftStickX * state->leftStickX +
                              state->leftStickY * state->leftStickY;
            if (deadZoneSquared <= leftMagSq) {
                inputActive = true;
            } else {
                // Check right stick magnitude
                float rightMagSq = state->rightStickX * state->rightStickX +
                                   state->rightStickY * state->rightStickY;
                if (deadZoneSquared <= rightMagSq) {
                    inputActive = true;
                }
            }
        }

        if (inputActive) {
            m_lastInputTime = g_currentTime;
        }
    }
}