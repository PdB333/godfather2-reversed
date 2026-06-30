// FUNC_NAME: UIScreen::processInputRumble
void __thiscall UIScreen::processInputRumble(int *thisPtr, int actionID) {
    int *controllerBase;
    int deviceState;

    // thisPtr[0x23] is at offset 0x8C, m_pInputDevice pointer
    // thisPtr[0x20] is at offset 0x80, m_lastAction
    // thisPtr[0x22] is at offset 0x88, m_hapticContext pointer
    if ((thisPtr[0x23] != 0) && (thisPtr[0x23] != (int)0x48)) {
        thisPtr[0x20] = actionID;                                     // +0x80: store action

        // The input device is embedded in a larger struct at offset 0x48.
        // Compute base of that containing struct.
        if (thisPtr[0x23] == 0) {
            controllerBase = (int *)0;
        } else {
            controllerBase = (int *)(thisPtr[0x23] - 0x48);
        }

        deviceState = *(int *)((int)controllerBase + 0x94);           // +0x94: m_deviceState (3,4,5,6)
        if ((((deviceState == 3) || (deviceState == 5)) ||
             (deviceState == 4) || (deviceState == 6)) {
            // If m_deviceState is one of 3,4,5,6, check secondary device pointer at +0x100
            if (thisPtr[0x23] == 0) {
                controllerBase = (int *)0;
            } else {
                controllerBase = (int *)(thisPtr[0x23] - 0x48);
            }
            if ((*(int *)((int)controllerBase + 100) != 0) &&
                (*(int *)((int)controllerBase + 100) != (int)0x48)) {
                // Play haptic effect using context data
                FUN_008b9050(thisPtr[0x22]);                          // playHapticEffect
            }
        }

        FUN_0072cb10(0);                                              // clearAction

        // Now decide which rumble pattern to play based on device state
        if (thisPtr[0x23] == 0) {
            controllerBase = (int *)0;
        } else {
            controllerBase = (int *)(thisPtr[0x23] - 0x48);
        }
        deviceState = *(int *)((int)controllerBase + 0x94);
        if ((deviceState == 3) || (deviceState == 5)) {
            // Trigger left/right rumble with pattern ID 0xd755f672
            (*(void (__thiscall **)(int, int, int, int, float, float))
             (*(int *)thisPtr + 0x2c))(0xd755f672, 1, 0, 0, 1.0f, 1.0f);
            return;
        }

        if (thisPtr[0x23] == 0) {
            controllerBase = (int *)0;
        } else {
            controllerBase = (int *)(thisPtr[0x23] - 0x48);
        }
        deviceState = *(int *)((int)controllerBase + 0x94);
        if ((deviceState == 4) || (deviceState == 6)) {
            // Trigger left/right rumble with pattern ID 0x46b13011
            (*(void (__thiscall **)(int, int, int, int, float, float))
             (*(int *)thisPtr + 0x2c))(0x46b13011, 1, 0, 0, 1.0f, 1.0f);
        }
    }
}