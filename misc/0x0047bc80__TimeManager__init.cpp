// FUNC_NAME: TimeManager::init
// Address: 0x0047bc80
// Role: One-time initialization of high-resolution timer, stores current time and computes a deadline based on an offset.
// Uses timeBeginPeriod/timeEndPeriod to get accurate timeGetTime, then records it.

#include <windows.h>
#include <mmsystem.h>

// Global flag: 0 = not initialized, non-zero = initialized
// Address: 0x012069d4
static int g_timerInitialized;

// Forward declarations for helper functions (not analyzed in this scope)
bool __fastcall isInitialized(int* pFlag);  // returns true if flag already set (atomic test)
void __fastcall copyTimerConfig(void* src, int* pFlag);  // copies config from object to global

void __thiscall TimeManager::init(void)
{
    bool bAlreadyInitialized;
    TIMECAPS timeCaps;
    DWORD currentTime;

    // Atomically check if timer already initialized
    bAlreadyInitialized = isInitialized(&g_timerInitialized);
    if (!bAlreadyInitialized)
    {
        // If flag non-zero (set by another thread?), copy timer config from object[' +0x3c ] to global
        if (g_timerInitialized != 0)
        {
            copyTimerConfig(reinterpret_cast<void*>(reinterpret_cast<DWORD>(this) + 0x3c), &g_timerInitialized);
        }

        // Get multimedia timer capabilities
        timeGetDevCaps(&timeCaps, sizeof(timeCaps));

        // Set minimum timer period for highest resolution
        timeBeginPeriod(timeCaps.wPeriodMin);

        // Capture current time with high precision
        currentTime = timeGetTime();

        // Restore previous timer resolution
        timeEndPeriod(timeCaps.wPeriodMin);

        // Store current time at offset +0x90
        *reinterpret_cast<DWORD*>(reinterpret_cast<DWORD>(this) + 0x90) = currentTime;

        // Compute and store deadline: base offset (+0x88) + current time
        *reinterpret_cast<DWORD*>(reinterpret_cast<DWORD>(this) + 0x8c) = 
            *reinterpret_cast<DWORD*>(reinterpret_cast<DWORD>(this) + 0x88) + currentTime;
    }
}