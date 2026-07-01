// FUNC_NAME: InputDeviceManager::updateRumbleTimeout
void __thiscall InputDeviceManager::updateRumbleTimeout(int thisPtr)
{
    int* pRumbleCounter;
    int currentThreadId;
    int gameMainLoopThreadId;
    unsigned int rumbleParam;
    int i;

    // Get current thread ID from thread manager (global at +0x4)
    currentThreadId = getCurrentThreadId(*(int*)((int)DAT_0112980c + 4));
    // Get ID of the game main loop thread (string "GameMainLoop")
    gameMainLoopThreadId = getThreadIdByName("GameMainLoop");

    // Decrement rumble timer (counter at +0x5c)
    pRumbleCounter = (int*)(thisPtr + 0x5c);
    *pRumbleCounter = *pRumbleCounter - 1;

    // If rumble timer expired and we're on the main loop thread, stop rumble
    if ((*pRumbleCounter == 0) && (currentThreadId == gameMainLoopThreadId))
    {
        // Disable rumble for all controllers
        setRumbleEnabled(1);
        // Stop current rumble effect
        clearRumbleEffect();
        // Set a low rumble motor speed (default 0xffdf)
        setRumbleMotorSpeed(1);

        // Determine rumble parameter: if the game is not in a special state
        rumbleParam = 0xffdf;
        // Check global input device manager pointer at +0x4
        if ((**(int**)((int)DAT_012233a0 + 4) != 0) && 
            (**(int**)((int)DAT_012233a0 + 4) != 0x1f30))
        {
            // If game is not suspended, use a different rumble value
            if (isGameSuspended() != '\0')
            {
                rumbleParam = 0xfadf;
            }
        }

        // Apply the rumble parameter to all 16 controller slots
        for (i = 0; i < 16; i++)
        {
            setControllerRumble(i, rumbleParam);
        }
    }
}