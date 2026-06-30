// FUNC_NAME: StreamManager::computeUpdateCount

/**
 * Function address: 0x0061eb30
 * Role: Computes the number of update ticks (or sample count) for an audio stream
 *       based on its frequency/interval and a global time scale.
 * Called from 0x4b3540 (likely audio update loop).
 * 
 * Parameters:
 *   this (ECX) - StreamManager instance (offset 0x98 = pointer to a Stream)
 * Returns: Number of ticks (0 if frequency is below threshold)
 */
__thiscall int StreamManager::computeUpdateCount(int this)
{
    int result = 0;  // local_8
    
    // Check if stream pointer is valid
    if (*(int*)(this + 0x98) != 0) {
        // Read frequency/interval from stream object (offset 0x1c8)
        float frequency = *(float*)(*(int*)(this + 0x98) + 0x1c8);
        
        // Compare against global threshold (likely minimum frequency)
        static float g_freqThreshold = *(float*)0x00e2b05c;  // DAT_00e2b05c
        if (g_freqThreshold < frequency) {
            // Get current time tick or random value from system
            int timeTick = getTimeTick();  // FUN_00d01890
            static float g_timeScale = *(float*)0x00e2e230;  // DAT_00e2e230
            
            // Compute tick count: (1/frequency) * timeTick * scale, rounded to int
            float invFreq = 1.0f / frequency;
            result = (int)ROUND(invFreq * (float)timeTick * g_timeScale);
        }
    }
    return result;
}