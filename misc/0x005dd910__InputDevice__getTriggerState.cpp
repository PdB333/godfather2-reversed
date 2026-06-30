// FUNC_NAME: InputDevice::getTriggerState
// Function at 0x005dd910 in Godfather 2 x86 binary.
// Determines whether a button press should be treated as a "trigger" (e.g., for analog action)
// based on a combination of global button masks and held state.

#include <cstdint>

// Global button mask constants (from external data).
// These define specific button groups used in the condition.
extern const uint32_t g_ButtonMask_0x00f15b80;  // Primary mask, e.g., face buttons (A,B,X,Y)
extern const uint32_t g_ButtonMask_0x00f15b78;  // Left group, e.g., D-pad
extern const uint32_t g_ButtonMask_0x00f15b7c;  // Right group, e.g., shoulder buttons
extern const uint32_t g_ButtonMask_0x012056c0;  // Special button mask, e.g., Start/Select

class InputDevice {
public:
    // Offset 0x2BC (700): bitfield of currently held buttons
    uint32_t m_heldButtons;

    // Offset 0x254: primary input value (e.g., digital button press state)
    int m_primaryState;

    // Offset 0x294: secondary input value (e.g., analog trigger value)
    int m_secondaryState;

    // Compares the requested button mask against global and internal state.
    // Returns m_secondaryState if the button combination is either:
    // - partially pressed (not fully covering combined D-pad+shoulder mask) AND 
    //   (special button pressed OR the pressed buttons are not currently held)
    // Otherwise returns m_primaryState.
    int getTriggerState(uint32_t buttonMask) {
        // Apply primary mask to filter out unwanted buttons
        uint32_t maskedButtons = g_ButtonMask_0x00f15b80 & buttonMask;

        // Combine left and right groups for comparison
        uint32_t combinedLeftRight = g_ButtonMask_0x00f15b78 | g_ButtonMask_0x00f15b7c;
        uint32_t leftRightButtons = combinedLeftRight & maskedButtons;

        // Check whether the button combination qualifies as a trigger:
        // Condition: left/right buttons are not fully pressed (i.e., not all required buttons)
        // AND (special button is pressed OR (some left/right buttons are pressed but NOT held))
        if (leftRightButtons != combinedLeftRight) {
            if ((g_ButtonMask_0x012056c0 & maskedButtons) != 0 ||
                (leftRightButtons != 0 && ((m_heldButtons & maskedButtons) == 0))) {
                // Trigger condition met: return secondary state (e.g., analog value)
                return m_secondaryState;
            }
        }
        // Default: return primary state (e.g., digital press)
        return m_primaryState;
    }
};