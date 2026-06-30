// FUNC_NAME: TimeUtils::validateTimeDelta

void __cdecl validateTimeDelta(float targetTime)
{
    // Get current engine time (likely from clock or timer, callee at 0x00470250)
    float currentTime = (float)FUN_00470250(); // returns 80-bit float, cast to 32-bit

    // Compute time difference
    float delta = targetTime - currentTime;

    if (delta > 0.0f)
    {
        // Clamp delta to targetTime if targetTime <= delta
        // This occurs when currentTime <= 0 (unusual but possible)
        if (targetTime <= delta)
        {
            delta = targetTime;
        }

        // Check against first global threshold (e.g., max allowed time)
        // _DAT_00d5780c likely represents a time limit
        if (gEngineMaxDeltaA < delta)
        {
            return; // Exit early if delta too large
        }
    }
    else
    {
        // Negative delta => set to zero (time not yet reached)
        delta = 0.0f;
    }

    // Check against second global threshold (e.g., secondary limit)
    // DAT_00d61ad4 might be another cap
    if (gEngineMaxDeltaB < delta)
    {
        return; // Exit early if delta still too large
    }

    // If neither early return triggered, the function does nothing else
    // Possibly used as a guard condition for subsequent operations
}