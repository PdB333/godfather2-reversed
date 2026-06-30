// FUNC_NAME: HighResTimer::getElapsedSeconds
float HighResTimer::getElapsedSeconds()
{
    LARGE_INTEGER current;
    QueryPerformanceCounter(&current);

    // Compute 64-bit difference in ticks (current - old)
    uint32_t deltaHigh = current.HighPart - m_oldHigh;
    uint32_t deltaLow = current.LowPart - m_oldLow;
    // If low part wrapped, borrow from high part
    if (current.LowPart < m_oldLow) {
        deltaHigh--;
    }

    // Convert to 64-bit signed value (ticks)
    int64_t ticks = ((int64_t)deltaHigh << 32) | deltaLow;

    // Convert ticks to seconds using the performance counter frequency
    // Note: The original code uses extended precision (float10) and handles sign,
    // but we assume positive elapsed time. The global _DAT_01163ed0 is the inverse
    // of the counter frequency (1/format(Frequency)).
    // For clarity, we use double conversion.
    return (float)((double)ticks * g_frequency);
}