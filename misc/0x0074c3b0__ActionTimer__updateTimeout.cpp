// FUNC_NAME: ActionTimer::updateTimeout

void __thiscall ActionTimer::updateTimeout(int thisPtr, uint currentTime)
{
    uint diff;
    int gameManagerPtr;
    uint64_t timeValue; // possibly a time struct
    uint32_t lowPart;
    float highPart;
    uint64_t param;

    // If the action object pointer is null, do nothing
    if (*(int*)(thisPtr + 0x88) != 0)
    {
        // Get stored start time
        uint startTime = *(uint*)(thisPtr + 0x80);
        
        // Compute absolute difference
        if (startTime < currentTime)
        {
            diff = currentTime - startTime;
        }
        else
        {
            diff = startTime - currentTime;
        }
        
        // If within acceptable time window (max 749 units)
        if (diff - 1 < 0x2ed) // diff <= 749
        {
            // Get game manager instance
            gameManagerPtr = FUN_00471610(); // getGameManager()
            
            // Read time-related data from game manager
            lowPart = *(uint32_t*)(gameManagerPtr + 0x30); // low part of time
            highPart = (float)((uint64_t)*(undefined8*)(gameManagerPtr + 0x30) >> 32); // high part as float
            
            // Construct the 64-bit parameter: high part as sum of float time component and a constant, low part as int
            uint64_t param = ((uint64_t)(highPart + DAT_00d6471c) << 32) | (uint64_t)lowPart;
            
            // Call the action object's virtual method (vtable offset 0x1c) with the parameter
            (**(code**)(**(int**)(thisPtr + 0x88) + 0x1c))(&param);
            return;
        }
        
        // If time difference > 750 units, treat as timeout
        if (diff > 0x2ee) // diff >= 751
        {
            // Clear bit 0 of the flags
            *(uint*)(thisPtr + 0xe4) &= 0xfffffffe;
            
            // Call deactivation/reset function
            FUN_005512c0(0); // deactivateAction()
        }
    }
    
    return;
}