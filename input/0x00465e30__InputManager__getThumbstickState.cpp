// FUNC_NAME: InputManager::getThumbstickState
// Address: 0x00465e30
// Reads thumbstick analog values from a controller slot. Supports 16 standard slots (0-15) and slot 0x11 for "any" controller.
// Controller slot structures are stored at gInputManager + 0x2c, each 0x44 bytes.
// param_3: 0 = left stick (X,Y), 1 = right stick (X,Y)
// param_6: if true, calls internal update member function
// param_7: if true, applies calibration using param_8 and param_9

void __thiscall InputManager::getThumbstickState(
    int slot,
    int stickIndex,
    float* outX,
    float* outY,
    bool bUpdate,
    bool bApplyCalibration,
    uint calibrationParam1,
    uint calibrationParam2)
{
    // Global pointer to main InputManager singleton
    extern InputManager* gInputManager; // DAT_012233b4

    float* pSlotData = nullptr;

    // Slot 0x12 (18) returns zeroed output
    if (slot == 0x12) {
        *outX = 0.0f;
        *outY = 0.0f;
        return;
    }

    // Slot 0x11 (17) uses a special "any" controller slot (likely virtual or keyboard/mouse)
    if (slot == 0x11) {
        pSlotData = (float*)((uintptr_t)gInputManager + 0x2c);
    }
    else if (slot <= 0xF) {
        // Normal slot (0-15) - each slot is 0x44 bytes from base+0x2c
        pSlotData = (float*)((uintptr_t)gInputManager + 0x2c + (uint)slot * 0x44);
    }
    else {
        // Invalid slot (not 0x11 or 0-15)
        *outX = 0.0f;
        *outY = 0.0f;
        return;
    }

    if (pSlotData == nullptr) {
        *outX = 0.0f;
        *outY = 0.0f;
        return;
    }

    // Read stick axis pair based on stick index
    if (stickIndex == 0) {
        // Left stick: offset 0 (X), offset 4 (Y)
        *outX = pSlotData[0];
        *outY = pSlotData[1];
    }
    else {
        // Right stick: offset 8 (X), offset 12 (Y)
        *outX = pSlotData[2];
        *outY = pSlotData[3];
    }

    // Optionally apply calibration (deadzone, sensitivity, etc.)
    if (bApplyCalibration) {
        FUN_00466280(calibrationParam1, calibrationParam2);
    }

    // Optionally update internal state (e.g., callback)
    if (bUpdate) {
        FUN_00465350(this);
    }
}