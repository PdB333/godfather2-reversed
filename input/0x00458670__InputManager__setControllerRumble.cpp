// FUNC_NAME: InputManager::setControllerRumble
// Address: 0x00458670
// Role: Sets rumble/vibration on a controller slot, clamping values between 0 and max limits.

void __thiscall InputManager::setControllerRumble(void* this, float leftMotor, float rightMotor)
{
    // This function is likely part of the input handling system.
    // DAT_01143360 is a pointer to a rumble engine/manager.
    // DAT_00e2b1a4 and DAT_00e4458c are maximum rumble values (typically 1.0f).

    if (DAT_01143360 == 0)
        return;

    // Controller slot index (must be < 8 for rumble? Possibly 8 max players)
    uint slot = in_EAX;
    if (slot >= 8)
        return;

    // +0x20: array of controller entries, each 0x10 bytes.
    // +0x00: pointer to ControllerState
    // +0x04: pointer to Device
    // Device +0x10: some handle/ID (possibly XInput device handle)
    int controllerEntry = *(int*)((slot + 2) * 0x10 + (int)this);
    if (controllerEntry == 0)
        return;
    int devicePtr = *(int*)(controllerEntry + 4);
    if (devicePtr == 0)
        return;
    int deviceHandle = *(int*)(devicePtr + 0x10); // Some handle

    // Call into rumble engine to begin setting rumble? (start transaction)
    FUN_00c9cbe0(DAT_01143360, deviceHandle, 0, &local_24);

    // Build a rumble command structure (likely VibrationPacket or similar)
    // Stack layout (starting from low address):
    //   uint8 local_24[8]    ; base
    //   float local_1c        ; right motor
    //   float local_14        ; left motor
    //   int local_c           ; flags/reserved
    // This is actually a contiguous structure used by FUN_00c9cd40.
    memset(&local_24, 0, sizeof(local_24)); // Clear the 8-byte base

    // Clamp parameters to valid range
    if (leftMotor > 0.0f) {
        if (leftMotor > DAT_00e2b1a4)
            leftMotor = DAT_00e2b1a4;
    } else {
        leftMotor = 0.0f;
    }
    if (rightMotor > 0.0f) {
        if (rightMotor > DAT_00e4458c)
            rightMotor = DAT_00e4458c;
    } else {
        rightMotor = 0.0f;
    }

    local_c = 0;                 // flags (maybe zero for normal)
    local_1c = rightMotor;       // motor values
    local_14 = leftMotor;

    FUN_00c9eac0();               // maybe begin transaction
    FUN_00c9cd40(0, &local_24);  // submit rumble command
    FUN_00c9eae0();               // end transaction

    return;
}