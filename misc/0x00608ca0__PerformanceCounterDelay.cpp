// FUNC_NAME: PerformanceCounterDelay
void PerformanceCounterDelay(int milliseconds)
{
    // +0x00: previous QPC low part
    // +0x04: previous QPC high part
    // (global: _DAT_01223530, _DAT_01223534)
    uint prevLow = _DAT_01223530;
    uint prevHigh = _DAT_01223534;

    // Global flag enabling this wait method
    if (DAT_0120575a != '\0' && milliseconds > 0)
    {
        LARGE_INTEGER currentCount;
        QueryPerformanceCounter(&currentCount);

        // Compute ticks elapsed since last recorded QPC
        uint tickDiffHigh = (currentCount.HighPart - prevHigh) - (uint)(currentCount.LowPart < prevLow);
        uint tickDiffLow = currentCount.LowPart - prevLow;

        // Convert requested milliseconds to target time (presumably in seconds)
        // _DAT_00e4465c is likely a conversion factor (0.001 to convert ms to seconds)
        float targetTime = (float)milliseconds * _DAT_00e4465c;

        // Loop until elapsed time >= target
        // _DAT_01163ec8 and DAT_00e2e230 are conversion factors from ticks to time
        while (true)
        {
            // Compute elapsed time from tick difference
            // The sign handling is messy; basically unsigned 64-bit difference
            uint uVar3 = tickDiffHigh; // after loop this gets updated
            // ... (complex sign cond) ...
            float elapsedTime = ...; // (tickDiff * _DAT_01163ec8) * DAT_00e2e230

            if (elapsedTime >= targetTime)
                break;

            // Yield CPU (likely Sleep(0) or equivalent)
            FUN_00ab4b40((uint*)0);

            QueryPerformanceCounter(&currentCount);
            tickDiffLow = currentCount.LowPart - prevLow;
            tickDiffHigh = (currentCount.HighPart - prevHigh) - (uint)(currentCount.LowPart < prevLow);
            uVar3 = tickDiffHigh & 0x7fffffff; // for sign handling
            // recompute elapsed, loop continues
        }
    }

    // Update previous QPC with last known value
    _DAT_01223534 = prevHigh;
    _DAT_01223530 = prevLow;
}