// FUNC_NAME: TimerManager::update

#include <windows.h>

// Global state (likely singleton)
extern CRITICAL_SECTION g_timerCriticalSection;  // 0x012224c0
extern int* g_timerListHead;                     // 0x012224ac
extern int g_timerCount;                         // 0x012224b4
extern LARGE_INTEGER g_lastQPC;                  // 0x01205858 (low), 0x0120585c (high)
extern double g_qpcToSeconds;                    // 0x01163ec8 (1 / QPC frequency)
extern double g_qpcToSecondsFast;                // 0x01163ecc (maybe same, used for elapsed check)
extern bool g_skipAllTimers;                     // 0x00f15a3a – byte flag
extern float g_highCountTimeScale;               // 0x00e2e230 – multiplier when timer count > 511

// Forward declarations of timer helper functions
void processExpiredTimer();      // FUN_0060ba00
void removeExpiredTimer();       // FUN_0060d1d0

// Timer node in the linked list
struct TimerNode {
    Timer* timer;                // +0x00: pointer to timer object
    TimerNode* next;             // +0x04: next node in list
};

// Timer object (incomplete – only known fields)
struct Timer {
    char pad1[0x1d];             // +0x00..0x1c
    char isPaused;               // +0x1d: 0 = active, non-zero = paused
    char pad2[0x06];             // +0x1e..0x23
    float remainingTime;         // +0x24: time left in seconds
};

// Main update: decrement all active timers, fire expired ones (with throttle)
void __thiscall TimerManager::update(float maxProcessingTime) {
    LARGE_INTEGER currentQPC;
    LARGE_INTEGER afterWorkQPC;
    bool throttle = false;            // bVar1 – suppress further triggers if too much time spent
    float deltaTime;                  // fStack_24

    QueryPerformanceCounter(&currentQPC);

    EnterCriticalSection(&g_timerCriticalSection);

    // Calculate elapsed time since last call (in seconds)
    __int64 elapsedTicks = currentQPC.QuadPart - g_lastQPC.QuadPart;  // low part difference handled via QuadPart
    // Decompiled does manual high/low splitting – but with QuadPart it's simpler
    // However we must match original behavior (signed? Actually using unsigned subtraction with borrow)
    // Original: iVar6 = local_20.s.LowPart - _DAT_01205858; uVar4 = (local_20.s.HighPart - _DAT_0120585c) - (uint)(local_20.s.LowPart < (uint)_DAT_01205858);
    // That's exactly calculating QuadPart difference with 64-bit borrow.
    // We'll assume QuadPart works.

    deltaTime = (float)(elapsedTicks * g_qpcToSeconds);
    // Update last QPC
    g_lastQPC = currentQPC;

    // Apply time scale if many timers (more than 511)
    if (g_timerCount > 511) {
        deltaTime *= g_highCountTimeScale;
    }

    // Iterate over timer list (linked list of TimerNode)
    TimerNode* node = (TimerNode*)g_timerListHead;  // piVar5
    while (node != nullptr) {
        Timer* timer = node->timer;       // iVar6 = *piVar5
        // Decrement remaining time
        timer->remainingTime -= deltaTime;

        // Check if timer expired and should be fired
        if ((!throttle && timer->remainingTime < 0.0f && timer->isPaused == 0) || g_skipAllTimers) {
            // Fire the timer
            processExpiredTimer();        // FUN_0060ba00
            removeExpiredTimer();         // FUN_0060d1d0

            // Measure time spent doing the work
            QueryPerformanceCounter(&afterWorkQPC);
            __int64 workTicks = afterWorkQPC.QuadPart - currentQPC.QuadPart;  // In original: iStack_10 = LStack_18.s.LowPart - uVar2; uVar4 = (LStack_18.s.HighPart - uVar3) - (uint)(LStack_18.s.LowPart < (uint)uVar2)
            float workTime = (float)(workTicks * g_qpcToSecondsFast);

            // If work took longer than maxProcessingTime, enable throttle
            if (workTime > maxProcessingTime) {
                throttle = true;
            }
        }

        // Advance to next node
        node = node->next;   // piVar5[1]
    }

    LeaveCriticalSection(&g_timerCriticalSection);
}