// FUNC_NAME: ControllerManager::getActionFromButtonState
// Address: 0x007c4090
// This function checks if specific buttons are pressed and if the corresponding action is allowed (via actionMask).
// It returns an action ID and a command code. Used for mapping controller input to game actions.

int ControllerManager::getActionFromButtonState(int actionMask, int* outActionId) {
    char buttonAState; // from button index 0x25
    char buttonBState; // from button index 0x26
    char buttonXState; // from button index 0x27
    int currentButtonPress;

    // Get pressed state for three buttons (likely A, B, X)
    buttonAState = isButtonPressed(getButtonState(0x25));
    buttonBState = isButtonPressed(getButtonState(0x26));
    buttonXState = isButtonPressed(getButtonState(0x27));

    // Check button A (0x25) - action mask bit 0x100
    if ((buttonAState != '\0') && (actionMask != 0) && ((*(uint*)(actionMask + 4) & 0x100) != 0)) {
        currentButtonPress = getCurrentButtonPress();
        if (currentButtonPress == 0x100) {
            *outActionId = 0;
            return 1; // command code for action A
        }
    }

    // Check button B (0x26) - action mask bit 0x200
    if ((buttonBState != '\0') && (actionMask != 0) && ((*(uint*)(actionMask + 4) & 0x200) != 0)) {
        currentButtonPress = getCurrentButtonPress();
        if (currentButtonPress == 0x200) {
            *outActionId = 1;
            return 0x201; // command code for action B
        }
    }

    // Check button X (0x27) - action mask bit 0x400
    if ((buttonXState != '\0') && (actionMask != 0) && ((*(uint*)(actionMask + 4) & 0x400) != 0)) {
        currentButtonPress = getCurrentButtonPress();
        if (currentButtonPress == 0x400) {
            *outActionId = 2;
            return 0x401; // command code for action X
        }
    }

    return 0; // no action triggered
}