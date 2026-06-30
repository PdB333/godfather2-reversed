// FUNC_NAME: getAbsoluteQpcTime

#include <windows.h>

// Static global variables representing the timer state
static unsigned long g_baseLow  = 0;  // DAT_01194b70
static unsigned long g_baseHigh = 0;  // DAT_01194b74
static unsigned long g_refLow   = 0;  // DAT_01194b78
static unsigned long g_refHigh  = 0;  // DAT_01194b7c

/**
 * Returns the current absolute QPC time by adding the offset (baseline)
 * to the elapsed time since a stored reference point.
 * The reference is presumably updated periodically to avoid wrapping issues.
 *
 * Implementation mimics the original x86 assembly: all arithmetic is
 * performed on 32-bit halves with explicit carry handling.
 */
unsigned long long getAbsoluteQpcTime(void)
{
    LARGE_INTEGER current;
    QueryPerformanceCounter(&current);

    unsigned long curLow  = current.LowPart;
    unsigned long curHigh = current.HighPart;

    // 64-bit unsigned comparison: current >= reference ?
    if ( (g_refHigh <= curHigh) &&
         ( (g_refHigh < curHigh) || (g_refLow < curLow) ) )
    {
        // Positive or zero difference: current - ref
        unsigned long diffLow  = curLow - g_refLow;
        unsigned long borrow   = (curLow < g_refLow) ? 1 : 0;
        unsigned long diffHigh = curHigh - g_refHigh - borrow;

        // Add difference to baseline, propagating carry from low addition
        unsigned long long sumLow  = (unsigned long long)diffLow + g_baseLow;
        unsigned long long sumHigh = (unsigned long long)diffHigh + g_baseHigh + (sumLow >> 32);

        return (sumHigh << 32) | (sumLow & 0xFFFFFFFF);
    }
    else
    {
        // Negative difference: current < ref, compute current - ref via
        // two's complement negation of (ref - current)
        // lowDiff = currentLow - refLow  (wrap)
        unsigned long diffLow  = curLow - g_refLow;
        unsigned long borrow   = (curLow < g_refLow) ? 1 : 0;
        unsigned long diffHigh = curHigh - g_refHigh - borrow;

        // Add negative difference to baseline (effectively subtract)
        unsigned long long sumLow  = (unsigned long long)diffLow + g_baseLow;
        unsigned long long sumHigh = (unsigned long long)diffHigh + g_baseHigh + (sumLow >> 32);

        return (sumHigh << 32) | (sumLow & 0xFFFFFFFF);
    }
}