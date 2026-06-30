// FUNC_NAME: InputManager::applyAnalogDeadzones
void InputManager::applyAnalogDeadzones(uint8_t analogMask) {
    // Global at 0x011f3c78: deadzone mask (which axes/triggers have deadzones applied)
    gDeadzoneMask = 0;
    if ((analogMask & 8) != 0) {
        gDeadzoneMask = 8; // bit 3: e.g., right trigger
    }
    if ((analogMask & 1) != 0) {
        gDeadzoneMask |= 1; // bit 0: e.g., left stick X
    }
    if ((analogMask & 2) != 0) {
        gDeadzoneMask |= 2; // bit 1: e.g., left stick Y
    }
    if ((analogMask & 4) != 0) {
        gDeadzoneMask |= 4; // bit 2: e.g., right stick X
    }

    // Clamp deadzone thresholds for two analog axes/sticks
    // gLeftDeadzone at 0x012058d4, gRightDeadzone at 0x00f1598c
    if (gLeftDeadzone < 0xA8) {
        gLeftDeadzone = 0xA8; // low deadzone threshold
    }
    if (gRightDeadzone > 0xA7) {
        gRightDeadzone = 0xA8; // force to low threshold if above
    }
    if (gLeftDeadzone < 0xBE) {
        gLeftDeadzone = 0xBE; // high deadzone threshold
    }
    if (gRightDeadzone > 0xBD) {
        gRightDeadzone = 0xBE; // force to high threshold if above
    }

    // Copy mask to output global at 0x011f3cd0
    gDeadzoneOutput = gDeadzoneMask;
}