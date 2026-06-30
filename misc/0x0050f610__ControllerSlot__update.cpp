// FUNC_NAME: ControllerSlot::update
void __thiscall ControllerSlot::update(float deltaTime) {
    uint *flagsPtr;
    short shortVal;
    char buttonResult;
    int deviceId;
    int *allocStack;
    int newDeviceId;
    int dummy3;

    // If a device is assigned and the slot is not marked as disconnected (0x20000 flag)
    if (*(int *)(this + 0xa0) != 0) {
        deviceId = *(int *)(this + 4);
        if ((*(uint *)(deviceId + 0xc) & 0x20000) == 0) {
            newDeviceId = 0;
            dummy3 = 0;
            if (*(int *)(deviceId + 0x20) != 0) {
                deviceId = *(int *)(deviceId + 0x20);
                if (deviceId != 0) {
                    // Reference count increment at offset +4
                    *(int *)(deviceId + 4) = *(int *)(deviceId + 4) + 1;
                }
                deviceId = FUN_00513f70(deviceId);  // Get current input device state
                if (deviceId != 0) {
                    dummy3 = *(int *)(deviceId + 0x24);
                    newDeviceId = *(int *)(deviceId + 0x28);
                }
            }
            // If the stored device ID has changed, update with locking
            if (*(int *)(this + 0xa0) != dummy3) {
                FUN_004f7bc0();  // Lock
                *(int *)(this + 0xa0) = dummy3;
                *(int *)(this + 0xa4) = newDeviceId;
                if (dummy3 != 0) {
                    FUN_004f7ba0();  // Unlock
                }
            }
        }
    }

    // Handle timer (e.g., for rumble / vibration duration)
    allocStack = *(int **)(unaff_FS_OFFSET + 0x2c);  // Get TLS allocation stack
    if ((0.0 < *(float *)(this + 0x4c)) && 
        (deltaTime = *(float *)(this + 0x4c) - deltaTime, *(float *)(this + 0x4c) = deltaTime, deltaTime <= 0.0)) {
        // Timer expired
        *(float *)(this + 0x4c) = *(float *)DAT_00e2eff4;  // Reset timer from global constant
        flagsPtr = (uint *)(*(int *)(*allocStack + 8) + *(int *)(this + 0x10));  // Per-slot flags (at slot index)
        *flagsPtr |= 1;  // Mark slot dirty
    }

    // Check for special button (e.g., X/Grab key)
    buttonResult = FUN_0050d950();
    if (buttonResult != 0) {
        // Set flag for action
        *(uint *)(this + 0x2c) |= 0x8000;
        flagsPtr = (uint *)(*(int *)(*allocStack + 8) + *(int *)(this + 0x10));
        *flagsPtr |= 1;  // Mark slot dirty
    }

    // Pack data for network/game state update
    shortVal = *(short *)(this + 0x58);  // Short value (e.g., sequence index)
    allocStack = (int *)(DAT_01206880 + 0x14);
    **(int **)(DAT_01206880 + 0x14) = &PTR_FUN_01125130;  // Set vtable pointer in global buffer
    *allocStack = *allocStack + 4;  // Advance the stack pointer
    FUN_00514080(this, CONCAT44((int)shortVal, this + 0xb0), 4);  // Write data to buffer
}