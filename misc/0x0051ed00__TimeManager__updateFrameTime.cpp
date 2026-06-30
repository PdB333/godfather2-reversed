// FUNC_NAME: TimeManager::updateFrameTime

void TimeManager::updateFrameTime(void)
{
    LARGE_INTEGER currentCounter;
    QueryPerformanceCounter(&currentCounter);

    // Check if current counter advance or wrap occurred.
    if ((s_lastCounterHigh <= (uint32_t)currentCounter.HighPart) &&
        ((s_lastCounterHigh < (uint32_t)currentCounter.HighPart ||
          (s_lastCounterLow < currentCounter.LowPart))))
    {
        // Normal forward progress: subtract to compute delta.
        s_elapsedLow = currentCounter.LowPart - s_lastCounterLow;
        s_elapsedHigh = (currentCounter.HighPart - s_lastCounterHigh) -
                        (uint32_t)(currentCounter.LowPart < s_lastCounterLow);
    }
    else
    {
        // Counter wrapped or went backwards: compute two's complement difference.
        s_elapsedLow = ~(s_lastCounterLow - currentCounter.LowPart) + 1;
        s_elapsedHigh = ~((s_lastCounterHigh - currentCounter.HighPart) -
                          (uint32_t)(s_lastCounterLow < currentCounter.LowPart)) +
                        (uint32_t)(0xFFFFFFFE < ~(s_lastCounterLow - currentCounter.LowPart));
    }
}