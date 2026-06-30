// FUNC_NAME: InputManager::updateMaxStickMagnitude

// 0x0051bc10 - Updates the maximum stick magnitude from all active controllers,
// stored at 'this' offsets +0x90 and +0x8c (both float).
void __thiscall InputManager::updateMaxStickMagnitude(void)
{
    int activeControllerCount;       // iVar1
    int controllerIndex;             // iVar2
    float maxMagnitude;              // local_10 / fVar3
    float currentMagnitude;          // local_8 (output from getControllerStickMagnitude)
    ControllerState* controllerArray; // base of DAT_01194ae0 (controller data array)

    // Global: DAT_01162387 - number of active controllers (non-zero check)
    if (gActiveControllerCount != 0)
    {
        activeControllerCount = (int)gActiveControllerCount;
        controllerIndex = 0;
        maxMagnitude = 0.0f;
        // Iterate over all active controllers
        do
        {
            // Call helper to get stick magnitude for current controller
            // FUN_0051b5f0 returns magnitude via out parameter (float*)
            getControllerStickMagnitude(&controllerArray[controllerIndex], &currentMagnitude);

            // Track the maximum magnitude seen so far
            if (maxMagnitude <= currentMagnitude)
            {
                maxMagnitude = currentMagnitude;
            }

            controllerIndex++;
            // fVar3 holds the same as maxMagnitude (redundant in original code)
        } while (controllerIndex < activeControllerCount);

        // Write the maximum magnitude to both controller deadzone or scaling fields
        // Offsets +0x90 and +0x8c are both float; possibly left/right or X/Y thresholds
        *(float*)((char*)this + 0x90) = maxMagnitude;
        *(float*)((char*)this + 0x8c) = maxMagnitude;
    }
    // If no active controllers, do nothing (magnitudes remain unchanged)
}