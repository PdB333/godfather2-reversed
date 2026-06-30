// FUNC_NAME: Profiler::trackProfileEvent
// Function at 0x00614da0 in Godfather 2 (x86, EARS engine)
// Tracks timing for specific event types using QueryPerformanceCounter.
// Accumulates total time into global 64-bit counter.
// Only active when profiling level (from 'this' in ESI) is 2 or 3.

#include <windows.h>

void Profiler::trackProfileEvent(uint param1, uint param2, int eventType, uint param4, uint param5, ushort param6, ushort param7)
{
    bool bShouldProfile;
    LARGE_INTEGER startTime, endTime;

    // Get start time before any processing
    QueryPerformanceCounter(&startTime);

    // Check if profiling is enabled (level 2 or 3)
    if (m_profileLevel == 3 || m_profileLevel == 2) {
        // Only profile specific event types
        switch (eventType) {
        case 0x1e: // 30
        case 0x1f: // 31
        case 0x20: // 32
        case 0x21: // 33
        case 0x22: // 34
            break;
        default:
            goto done;
        }

        // Determine if this event should be profiled (additional events)
        if ((eventType == 0x20) || (eventType == 0x21) || (eventType == 0x1f) ||
            (eventType == 5) || (eventType == 4) || (eventType == 3) || (eventType == 7)) {
            bShouldProfile = true;
        } else {
            bShouldProfile = false;
        }

        // Call the actual event processing function
        processProfileEvent(param1, param2, param4, param5, param6, param7, bShouldProfile);

        // Get end time after event processing
        QueryPerformanceCounter(&endTime);

        // Accumulate time difference into global 64-bit total
        // _DAT_01205950 and _DAT_01205954 form a 64-bit integer
        __int64 diff = (__int64)(endTime.QuadPart - startTime.QuadPart);
        gProfilerTotalTime += diff;
    }

done:
    return;
}