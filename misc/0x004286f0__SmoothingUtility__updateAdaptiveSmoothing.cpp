// FUNC_NAME: SmoothingUtility::updateAdaptiveSmoothing
// Address: 0x004286f0
// Role: Adaptive low-pass smoother for time-series data (e.g., audio/input parameters).
// Updates a smoothing factor and computes a smoothed output based on the difference
// between a current and previous value. Intended to be called each frame.

// Global variables (offsets are arbitrary; these are standalone globals):
// s_currentTime   (DAT_01163cac) – current time or sample value
// s_previousTime  (DAT_01163cb4) – previous time or sample value
// s_smoothingFactor (DAT_0110ac50) – adaptive coefficient (0..n)
// s_smoothedOutput   (DAT_0110b76c) – result of smoothing

void SmoothingUtility::updateAdaptiveSmoothing(void)
{
    int diff = s_currentTime - s_previousTime;   // difference between current and previous values

    if (diff > 128)                               // only smooth if difference exceeds threshold
    {
        // Check if the difference lies outside the current smoothing window
        // (window size = s_smoothingFactor * 128, centered on that value)
        if ((s_smoothingFactor * 128 < diff) ||
            (diff < s_smoothingFactor * 128 - 128))
        {
            // Recalculate smoothing factor as diff divided by 128
            s_smoothingFactor = diff >> 7;        // equivalent to diff / 128
        }

        // Compute smoothed output: difference divided by (smoothing factor + 1)
        s_smoothedOutput = diff / (s_smoothingFactor + 1);
    }
    else
    {
        s_smoothingFactor = 0;
        s_smoothedOutput = 0;
    }
}