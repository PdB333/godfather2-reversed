// FUNC_NAME: GameManager::performTick
void GameManager::performTick()
{
    // Clear some state parameters (possibly animation or input flags)
    clearStateParameters(0, 0, 0);

    // Call virtual method at vtable offset 0x2c (probably update or process)
    (*(this->vtablePtr + 0x2c))(this);

    // Check if a global time threshold (0x0c = 12) has been exceeded
    if (globalTimeThreshold > 12)
    {
        // Set a global state to '12' (might be maximum steps or a clamped value)
        globalStepCounter = 12;

        // Reset a field at offset +0x60 in a global manager object
        *(reinterpret_cast<int*>(globalManagerObject + 0x60)) = 0;

        // If the initialization flag is not set, register a callback with a target label
        if ((globalInitFlags & 1) == 0)
        {
            registerCallback(globalManagerObject + 0x14, &callbackLabel, 0);
            globalInitFlags |= 1;
        }
    }
}