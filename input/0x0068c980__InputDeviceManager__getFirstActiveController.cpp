// FUNC_NAME: InputDeviceManager::getFirstActiveController
uint __fastcall InputDeviceManager::getFirstActiveController(InputDeviceManager* this)
{
    float fDeadzone;                     // deadzone threshold (not squared)
    float* pControllerState;             // pointer to controller state struct
    uint uIndex;                         // loop counter
    float fDeadzoneSq;                   // squared deadzone threshold

    // +0x2c: flag indicating whether controller input is active/enabled
    if (*(int*)((uint)this + 0x2c) != 0) {
        // global config pointer at DAT_01223464; +0x1694 is deadzone magnitude
        fDeadzone = *(float*)(*(uint*)0x01223464 + 0x1694);
        fDeadzoneSq = fDeadzone * fDeadzone;
        uIndex = 0;
        do {
            // Get pointer to controller state for slot uIndex
            pControllerState = (float*)FUN_00410540(uIndex);
            if (pControllerState != (float*)0x0 &&
                // +0x3e: connection status byte (non-zero means connected)
                *(char*)((uint)pControllerState + 0x3e) != '\0' &&
                // Check if any button is pressed (low 14 bits of buttonFlags at +0x10)
                (((uint)pControllerState[4] & 0x3fff) != 0 ||
                 // Or if left stick magnitude squared >= deadzone squared
                 (fDeadzoneSq <= pControllerState[0] * pControllerState[0] + pControllerState[1] * pControllerState[1]) ||
                 // Or if right stick magnitude squared >= deadzone squared
                 (fDeadzoneSq <= pControllerState[2] * pControllerState[2] + pControllerState[3] * pControllerState[3])))
            {
                return uIndex & 0xff;  // Return controller index (0-15)
            }
            uIndex = uIndex + 1;
        } while (uIndex < 0x10); // 16 controller slots
    }
    return 0x12; // No active controller found (18 = "none" value)
}