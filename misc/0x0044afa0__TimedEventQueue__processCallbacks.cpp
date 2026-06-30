// FUNC_NAME: TimedEventQueue::processCallbacks
// Function at 0x0044afa0: Processes a circular buffer of timed callbacks. 
// Waits up to a time limit (param_2/param_3 as 64-bit QPC ticks) then processes 
// any callbacks whose scheduled time (in ms) has elapsed.
// Returns true if any callbacks remain pending after processing.

#include <windows.h> // For LARGE_INTEGER, QueryPerformanceCounter

// Forward declaration of the function called for each callback
void dispatchCallback(uintptr_t context); // FUN_0044a0e0

// External global variables – likely set during initialization
extern uint64_t g_qpcFrequency;            // DAT_01163ec0 (low) + DAT_01163ec4 (high)
extern float g_qpcToSeconds;              // DAT_01163ecc (1/frequency in seconds? or ms?)
extern float g_someOffset;                // DAT_01227894 (calibrated offset, maybe overhead)
extern int g_calibrationFlag;             // DAT_01227898 (bit0 used as one-time init flag)
extern float g_timeScale;                 // DAT_00e44578 (used for negative float correction)

bool __thiscall TimedEventQueue::processCallbacks(uint32_t timeLimitLow, uint32_t timeLimitHigh)
{
    int i;
    uint32_t uVar2;
    LARGE_INTEGER currentTime;
    LARGE_INTEGER limit;
    LARGE_INTEGER startTime;
    LARGE_INTEGER elapsed;
    double fElapsed, fLimit;
    int64_t deltaMs;
    uint32_t elapsedMs;
    float thresholdMs;

    // Construct the time limit as a signed 64-bit integer (absolute value)
    limit.HighPart = timeLimitHigh & 0x80000000; // preserve sign bit
    limit.LowPart = 0;

    // Reciprocal of QPC frequency (to convert ticks to seconds)
    double freqRecip = (double)g_qpcToSeconds;

    // Get starting timestamp
    QueryPerformanceCounter(&startTime);

    // First pass: process all pending callbacks within the time limit
    while (pendingCount != 0)
    {
        // Current read index in the circular buffer
        i = currentIndex;
        // Fetch the two fields of the entry
        uintptr_t context = buffer[i * 2];   // +0x00: callback context
        uint32_t scheduledTime = buffer[i * 2 + 1]; // +0x04: scheduled timestamp (ms)

        // Advance index
        currentIndex = i + 1;
        if (currentIndex >= bufferCapacity)
            currentIndex = 0;

        pendingCount--;

        // Execute the callback
        dispatchCallback(context);

        // Measure elapsed time since start
        QueryPerformanceCounter(&currentTime);
        elapsed.LowPart = currentTime.LowPart - startTime.LowPart;
        elapsed.HighPart = currentTime.HighPart - startTime.HighPart;
        if (currentTime.LowPart < startTime.LowPart) elapsed.HighPart--;

        // Convert elapsed ticks to seconds using frequency reciprocal
        fElapsed = (double)(elapsed.QuadPart) * freqRecip;

        // Convert limit to seconds (handle sign bit correctly)
        limit.QuadPart = (int64_t)(((uint64_t)timeLimitHigh << 32) | timeLimitLow);
        fLimit = fabs((double)limit.QuadPart * freqRecip);

        // Break if we've exceeded the allowed time
        if (fElapsed > fLimit)
            break;
    }

    // If there are still pending callbacks, try to process ones that have reached their scheduled time
    if (pendingCount != 0)
    {
        // Get current time to compute elapsed since last "base" timestamp stored in this object
        QueryPerformanceCounter(&currentTime);

        // Compute milliseconds elapsed since the last recorded QPC value (stored at offsets +8/+0xc)
        int64_t deltaTicks;
        deltaTicks = ((int64_t)(currentTime.HighPart - baseTimeHigh) << 32) |
                     (uint64_t)(currentTime.LowPart - baseTimeLow);
        if (currentTime.LowPart < baseTimeLow) deltaTicks -= (1ULL << 32); // correct borrow

        // Convert to milliseconds: deltaTicks * 1000 / frequency
        deltaMs = (uint32_t)((__allmul((uint32_t)(deltaTicks & 0xFFFFFFFF), (uint32_t)(deltaTicks >> 32), 1000, 0) /
                              g_qpcFrequency.low) & 0xFFFFFFFF);
        // Actually the code uses __allmul with (low,high,1000,0) and then __aulldiv by frequency.
        // Simplified for readability:
        // deltaMs = (deltaTicks * 1000) / g_qpcFrequency;

        // One-time calibration: store the scaled conversion factor for later use
        if ((g_calibrationFlag & 1) == 0)
        {
            g_calibrationFlag |= 1;
            double freqFloat = (double)(g_qpcFrequency & 0x7FFFFFFFFFFFFFFF);
            g_someOffset = (float)(freqFloat / g_timeScale);  // ROUND of something
            // Actually the code does: 
            // local_18 = (LARGE_INTEGER)((ulonglong)(uVar6 & 0x80000000) << 0x20);
            // local_18 = ROUND(( - (float10)(longlong)local_18 + fVar7) / (float10)DAT_0110ae4c);
            // _DAT_01227894 = (float)(int)local_18.s.LowPart;
            // It's a calibration constant. We'll keep as is.
        }

        // Process callbacks sorted by scheduled time (circular buffer may not be sorted, but we iterate in stored order)
        while (pendingCount != 0)
        {
            thresholdMs = (float)timeThreshold;  // Some threshold stored at +0x10, possibly an interval

            // Check if the next pending callback's scheduled time has passed
            i = currentIndex;
            uint32_t entryScheduledTime = buffer[i * 2 + 1]; // +0x04
            uint32_t elapsedSinceScheduled = deltaMs - entryScheduledTime;

            // If (elapsedSinceScheduled + g_someOffset) <= thresholdMs, break (not yet ready)
            if ((float)elapsedSinceScheduled + g_someOffset <= thresholdMs)
                break;

            // Otherwise, process this callback
            uintptr_t context = buffer[i * 2];
            currentIndex = i + 1;
            if (currentIndex >= bufferCapacity)
                currentIndex = 0;
            pendingCount--;
            dispatchCallback(context);
        }
    }

    // Return true if there are still pending callbacks
    return pendingCount != 0;
}