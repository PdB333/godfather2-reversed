// FUNC_NAME: ControllerState::updateInputs
void __thiscall ControllerState::updateInputs(
    ControllerState *pThis,
    int *pLeftStickX,       // output: left analog X (+0x00)
    int *pLeftStickY,       // output: left analog Y (+0x04)
    int *pRightStickX,      // output: right analog X (+0x08)
    int *pRightStickY,      // output: right analog Y (+0x0C)
    int deadZone,           // dead zone threshold (copied to analog reads)
    int sensitivity,        // sensitivity scaling (copied to analog reads)
    char *pActiveFlag,      // output: if stick is active (non-zero)
    char *pButtonState)     // output: extra button state (e.g., action)
{
    // Global input device state pointer (from EARS InputManager, likely +0x4 offset)
    // DAT_012233a0 is believed to be the InputManager singleton
    int *inputDeviceState = *(int **)(*(int *)(DAT_012233a0 + 4));

    // Check if input is allowed (not in menu, not paused, etc.)
    bool skipInput = false;
    if (inputDeviceState == 0 || inputDeviceState == (int*)0x1f30)
    {
        skipInput = true;
    }
    else if (((*(uint *)((int)inputDeviceState + 0x570) >> 0x14) & 1) == 0) // bit 20? likely "input active" flag
    {
        skipInput = true;
    }

    if (skipInput ||
        (*(int *)((int)pThis + 0x6c) == -1) ||   // controller slot unassigned?
        (DAT_00e50fb5 == '\0'))                    // global input enable byte?
    {
        // Inputs not valid – zero all outputs
        *pLeftStickX = 0;
        *pLeftStickY = 0;
        *pRightStickX = 0;
        *pRightStickY = 0;
        *pActiveFlag = 0;
        *pButtonState = 0;
        return;
    }

    // Read left analog stick (index 0)
    FUN_006c9eb0(0, pLeftStickX, pLeftStickY, deadZone, sensitivity);
    // Read right analog stick (index 1)
    FUN_006c9eb0(1, pRightStickX, pRightStickY, deadZone, sensitivity);

    // Get active flag (likely if either stick is moved beyond dead zone)
    *pActiveFlag = FUN_006c9fe0();

    // Get extra button state (e.g., "use" or "fire" button)
    *pButtonState = 0;
    if ((*(int *)((int)pThis + 0x6c) != -1) && (DAT_00e50fb5 != '\0'))
    {
        // FUN_00410280: button state query (takes controller slot, button ID 1, and type 2)
        *pButtonState = FUN_00410280(*(unsigned char *)((int)pThis + 0x6c), 1, 2);
    }
}