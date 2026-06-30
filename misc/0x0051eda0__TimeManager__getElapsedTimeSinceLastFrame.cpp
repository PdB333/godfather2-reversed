// FUNC_NAME: TimeManager::getElapsedTimeSinceLastFrame
#include <windows.h>  // For QueryPerformanceCounter, LARGE_INTEGER

// Global static variables storing the previous frame's high-resolution timer value
// +0x0: LowPart of previous timestamp
// +0x4: HighPart of previous timestamp
extern uint32_t DAT_01194b78;  // Previously saved LowPart (QPC value)
extern uint32_t DAT_01194b7c;  // Previously saved HighPart (QPC value)
extern uint32_t DAT_01194b70;  // Accumulated frame time low part (in QPC units)
extern uint32_t DAT_01194b74;  // Accumulated frame time high part

uint64_t TimeManager::getElapsedTimeSinceLastFrame(void)
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);

    // Check if current time is after or equal to previous timestamp (normal case)
    // Compare high parts first, then low parts if high parts are equal
    if ((DAT_01194b7c <= (uint32_t)currentTime.HighPart) &&
        ((DAT_01194b7c < (uint32_t)currentTime.HighPart) || 
         (DAT_01194b78 < currentTime.LowPart))) 
    {
        // Normal case: current >= previous (time advanced forward)
        // Compute the time difference: current - previous + accumulated frame time
        uint64_t diffLow = currentTime.LowPart - DAT_01194b78;
        uint64_t diffHigh = (currentTime.HighPart - DAT_01194b7c) - 
                            (uint32_t)(currentTime.LowPart < DAT_01194b78);
        
        uint64_t diffLow2 = DAT_01194b70 + diffLow;
        uint64_t diffHigh2 = DAT_01194b74 + diffHigh + 
                             (uint32_t)CARRY4(DAT_01194b70, diffLow);
        
        return CONCAT44(diffHigh2, diffLow2);
    }
    else 
    {
        // Current time is before previous timestamp (counter wrapped around or overflow)
        // Compute the difference by wrapping around the 64-bit value
        uint32_t wrappedLow = ~(DAT_01194b78 - currentTime.LowPart) + 1; // Equivalent to (DAT_01194b78 - currentTime.LowPart) negated
        
        uint32_t borrow = (uint32_t)(DAT_01194b78 < currentTime.LowPart);
        uint32_t wrappedHigh = ~((DAT_01194b7c - currentTime.HighPart) - borrow) + 
                               (uint32_t)(0xfffffffe < wrappedLow) +
                               (uint32_t)CARRY4(DAT_01194b70, wrappedLow);
        
        uint64_t resultLow = DAT_01194b70 + wrappedLow;
        uint64_t resultHigh = DAT_01194b74 + wrappedHigh;
        
        return CONCAT44(resultHigh, resultLow);
    }
}