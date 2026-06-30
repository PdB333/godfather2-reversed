// FUNC_NAME: getHighPrecisionTimerValue
// Function address: 0x0065c340
// Returns a high-precision timer value (tick count or performance counter).
// Includes optional profiling hooks for performance monitoring.

#include <windows.h>

// Global state (defined elsewhere)
extern int g_timerMode;          // DAT_01205a68 - 0,1,2
extern bool g_useHighPrecisionTimer; // DAT_0120589a
extern bool g_usePerformanceCounter; // DAT_01223370
extern uint32_t g_profileFlags;  // DAT_01226648
extern char* g_profileString1;   // DAT_01226630
extern int g_profileLine1;       // DAT_01226634
extern void* g_profilePrev1;     // DAT_01226638
extern void* g_profileStack;     // DAT_01205a84
extern uint32_t g_profileCounter; // DAT_01205a80
extern uint32_t g_profileMaxCount; // DAT_01205a7c
extern bool g_someFlag;          // DAT_01127d3c
extern uint32_t g_someCounter;   // DAT_01127d38
extern uint32_t g_someThreshold; // DAT_01205a6c

// Forward declarations of helper functions (defined elsewhere)
void profileBegin(const char* name); // FUN_0065f6b0
void logProfileData(int type, void* data); // FUN_0064b810
void profileEnd(); // FUN_0065fab0
void logProfileData2(int type, void* data); // FUN_0064b9e0

uint32_t getHighPrecisionTimerValue(void)
{
    LARGE_INTEGER counter;
    uint32_t lowPart;
    uint32_t highPart;

    // Branch based on timer mode and high-precision flag
    if ((g_timerMode != 2) || (!g_useHighPrecisionTimer))
    {
        // Use GetTickCount or QueryPerformanceCounter based on flag
        if (g_usePerformanceCounter)
        {
            QueryPerformanceCounter(&counter);
            lowPart = counter.LowPart;
            highPart = counter.HighPart;
        }
        else
        {
            lowPart = GetTickCount();
            highPart = 0;
        }

        // If mode is 1 and high-precision timer is active, profile this call
        if ((g_timerMode == 1) && (g_useHighPrecisionTimer))
        {
            // Set up profiling event
            if ((g_profileFlags & 2) == 0)
            {
                g_profileFlags |= 2;
                g_profileString1 = "getHighPrecisionTimerValue";
                g_profileLine1 = -1;
                g_profilePrev1 = g_profileStack;
                g_profileStack = &g_profileString1;
            }
            profileBegin(&g_profileString1);
            counter.LowPart = lowPart;
            counter.HighPart = highPart;
            logProfileData(0x40, &counter);
            profileEnd();
        }
        return lowPart;
    }
    else
    {
        // Alternative profiling path (mode 2 with high-precision timer)
        if ((g_profileFlags & 1) == 0)
        {
            g_profileFlags |= 1;
            g_profileString1 = "getHighPrecisionTimerValue";
            g_profileLine1 = -1;
            g_profilePrev1 = g_profileStack;
            g_profileStack = &g_profileString1;
        }
        profileBegin(&g_profileString1);
        g_profileCounter++;
        if ((g_profileMaxCount != 0) && (g_profileMaxCount <= g_profileCounter))
        {
            // Debug breakpoint (software interrupt 3)
            __debugbreak();
        }
        logProfileData2(0x40, &counter);
        if ((!g_someFlag) && (g_someCounter < g_someThreshold))
        {
            return counter.LowPart;
        }
        // Another debug breakpoint
        __debugbreak();
        return 0; // Fallback (unreachable if breakpoint triggers)
    }
}