// Xbox PDB: TNL::Platform::getRealMilliseconds
// FUNC_NAME: getRealMilliseconds
// Address: 0x0065c190
// Role: Custom timer function with profiling hooks. Returns milliseconds since system start.
// Uses global profiling state to track calls and optionally trigger debug breaks.

#include <windows.h>

// Global profiling state (offsets relative to base)
extern int g_timeMode;                // +0x01205a68: 0=normal, 1=profile mode1, 2=profile mode2
extern bool g_timeProfilingEnabled;   // +0x0120589a
extern int g_profilingFlags;          // +0x01225d68: bit0=mode2 active, bit1=mode1 active
extern const char* g_profilingString1; // +0x01225d50
extern int g_profilingInt1;           // +0x01225d54
extern void* g_profilingPrev1;        // +0x01225d58
extern void* g_profilingListHead;     // +0x01205a84: linked list head for profiling entries
extern const char* g_profilingString2; // +0x01225d5c
extern int g_profilingInt2;           // +0x01225d60
extern void* g_profilingPrev2;        // +0x01225d64
extern int g_timeCallCount;           // +0x01205a80
extern int g_timeCallLimit;           // +0x01205a7c: if non-zero, break after this many calls
extern bool g_someFlag;               // +0x01127d3c
extern int g_someCounter;             // +0x01127d38
extern int g_someThreshold;           // +0x01205a6c

// Forward declarations of profiling helper functions
void profilingPush(const char* name);      // 0x0065f6b0
void profilingLog(int param, void* data);  // 0x0064b810
void profilingPop(void);                   // 0x0065fab0
void profilingEnd(int param, void* data);  // 0x0064b9e0

// Debug break helper (software interrupt 3)
inline void debugBreak(void) {
    __asm { int 3 }
}

DWORD getRealMilliseconds(void)
{
    DWORD tickCount;
    DWORD result;

    if (g_timeMode != 2 || !g_timeProfilingEnabled)
    {
        // Mode 0 or 1 (or profiling disabled)
        tickCount = GetTickCount();

        if (g_timeMode == 1 && g_timeProfilingEnabled)
        {
            // Initialize profiling entry for mode 1 if not already done
            if ((g_profilingFlags & 2) == 0)
            {
                g_profilingFlags |= 2;
                g_profilingString1 = "getRealMilliseconds";
                g_profilingInt1 = 0xFFFFFFFF;
                g_profilingPrev1 = g_profilingListHead;
                g_profilingListHead = &g_profilingString1;
            }

            profilingPush(&g_profilingString1);
            result = tickCount;
            profilingLog(0x20, &result);
            profilingPop();
        }

        return tickCount;
    }
    else
    {
        // Mode 2 with profiling enabled
        if ((g_profilingFlags & 1) == 0)
        {
            g_profilingFlags |= 1;
            g_profilingString2 = "getRealMilliseconds";
            g_profilingInt2 = 0xFFFFFFFF;
            g_profilingPrev2 = g_profilingListHead;
            g_profilingListHead = &g_profilingString2;
        }

        profilingPush(&g_profilingString2);
        g_timeCallCount++;

        if (g_timeCallLimit != 0 && g_timeCallCount >= g_timeCallLimit)
        {
            // Trigger debug break and call handler
            debugBreak();
            // Note: original code calls the result of swi(3) as a function pointer
            // We simulate by returning whatever the debug handler would return
            // For simplicity, we just break and return 0
            return 0;
        }

        profilingEnd(0x20, &result);

        if (g_someFlag == 0 && g_someCounter < g_someThreshold)
        {
            return result;
        }

        // Condition failed – trigger debug break
        debugBreak();
        return 0;
    }
}