// FUNC_NAME: sleepForMilliseconds
void sleepForMilliseconds(int ms)
{
    // Global state: performance counter last value (64-bit), frequency data, and initialization flag
    extern unsigned int g_perfCounterLow;   // _DAT_01223530
    extern unsigned int g_perfCounterHigh;  // _DAT_01223534
    extern bool g_timerInitialized;        // DAT_0120575a (byte)
    extern double g_ticksPerMillisecond;   // _DAT_00e4465c (float10)
    extern double g_reciprocalFrequency;   // _DAT_01163ec8 (float10)
    extern double g_frequency;             // DAT_00e2e230 (float10)

    unsigned int lastLow = g_perfCounterLow;
    unsigned int lastHigh = g_perfCounterHigh;

    if (g_timerInitialized && (ms > 0)) {
        LARGE_INTEGER current;
        QueryPerformanceCounter(&current);

        // Compute elapsed counts since last recorded counter (handle 64‑bit wrap)
        unsigned int highDiff = current.HighPart - lastHigh;
        unsigned int lowDiff = current.LowPart - lastLow;
        unsigned int borrowed = (current.LowPart < lastLow) ? 1 : 0;
        unsigned long long elapsedCounts = ((unsigned long long)(highDiff - borrowed) << 32) | lowDiff;

        // Desired counts = ms * ticks per millisecond
        double desiredCounts = (double)ms * g_ticksPerMillisecond;

        // Busy‑wait loop until elapsed time reaches the desired duration
        while (true) {
            // Convert elapsed counts to seconds, then compare to desired counts
            // Note: The original uses extended‐precision x87 operations; approximated here as double.
            // (elapsedCounts) * g_reciprocalFrequency * g_frequency  yields elapsedCounts in some scaled unit.
            double elapsedTime = ((double)(long long)(elapsedCounts & 0x7FFFFFFFFFFFFFFF))
                                 // Handle sign? Original code subtracts the negative part; we assume non‑negative.
                                 * g_reciprocalFrequency * g_frequency;
            if (elapsedTime >= desiredCounts) {
                break;
            }

            // Yield the thread (e.g., Sleep(0)) to avoid monopolising the CPU
            unsigned int yieldParam = 0;
            FUN_00ab4b40(&yieldParam);   // external function that yields

            // Re‑read the performance counter
            QueryPerformanceCounter(&current);
            lowDiff = current.LowPart - lastLow;
            highDiff = current.HighPart - lastHigh;
            borrowed = (current.LowPart < lastLow) ? 1 : 0;
            elapsedCounts = ((unsigned long long)(highDiff - borrowed) << 32) | lowDiff;
        }
    }

    // Update the last recorded counter value
    g_perfCounterLow = lastLow;
    g_perfCounterHigh = lastHigh;
}