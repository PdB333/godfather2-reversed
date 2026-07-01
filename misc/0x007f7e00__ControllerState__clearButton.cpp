// FUNC_NAME: ControllerState::clearButton
// Function at 0x007f7e00: Clears a button flag from current/previous states, resets analog and rumble fields.
// If the button index is 9 (likely "Start" or special), calls stopRumble().

// Assumed structure offsets (based on bitfield operations and large offset):
struct ControllerState {
    // +0x604: current frame button bitmask
    uint32_t buttonsCurrent;
    // +0x608: previous frame button bitmask
    uint32_t buttonsPrevious;
    // +0x60c: analog value for this button (e.g., trigger/thumbstick)
    int32_t analogValue;
    // +0x1b90: rumble state (0 = off)
    int32_t rumbleState;
};

// Forward declaration of external function (likely stops rumble for this controller)
void stopRumble(void); // at 0x00549cf0

void __thiscall ControllerState::clearButton(byte buttonIndex) {
    // Build mask with all bits set except the one corresponding to buttonIndex
    uint32_t mask = ~(1 << (buttonIndex & 0x1f));

    // Clear the bit in both current and previous button states
    buttonsCurrent &= mask;
    buttonsPrevious &= mask;

    // Reset analog value (e.g., trigger pressure or thumbstick axis)
    analogValue = 0;
    // Reset rumble state (stop vibration)
    rumbleState = 0;

    // Special handling for button index 9 (e.g., "Start" on Xbox controller)
    if (buttonIndex == 9) {
        stopRumble();
    }
}