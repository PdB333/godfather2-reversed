// FUNC_NAME: TimerManager::updateTimers

// 0060c5e0 - TimerManager::updateTimers(float maxFrameTime)
// Processes all timers, decrementing their remaining time by the frame delta.
// If a timer expires and it's not paused (or a global override flag is set),
// it fires the timer callbacks (FUN_0060c430 and FUN_0060d3f0).
// Processing is bounded by maxFrameTime to avoid starving the main loop.

#include <windows.h>

// Structure for a timer node (speculative based on offsets)
struct TimerNode {
    void* prev;           // +0x00 (not used in this function, but likely linked list)
    TimerNode* next;      // +0x04
    // ... other fields ...
    bool paused;          // +0x29
    float remainingTime;  // +0x30
};

// Global linked list head (pointer to first node)
TimerNode* g_timerListHead; // DAT_012224e0

// Global counter, when > 0x1ff, use a time scale multiplier
int g_timerCounter; // DAT_012224e8

// Time scale multiplier applied when counter > 0x1ff
float g_timerTimeScale; // DAT_00e2e230

// Critical section protecting timer list
CRITICAL_SECTION g_timerCriticalSection; // DAT_012224f8

// Last performance counter values for delta time calculation
LARGE_INTEGER g_lastPerformanceCounterLow;  // _DAT_01205860 (low part)
LARGE_INTEGER g_lastPerformanceCounterHigh; // _DAT_01205864 (high part)

// Conversion factors from performance counter ticks to seconds
// These are likely 1.0 / frequency (counter ticks per second)
double g_qpcToSeconds; // _DAT_01163ec8 (maybe multiplied by some constant?)
double g_limitCheckToSeconds; // _DAT_01163ecc (used for max frame time check)

// External timer callback functions (likely dispatch to timer handler)
void timerTimerExpired(); // 0x0060c430
void timerHandleTimeOut(); // 0x0060d3f0

// Global flag that disables timer limit check
bool g_disableTimerLimit; // DAT_00f15a3a

void TimerManager::updateTimers(float maxFrameTime)
{
    LARGE_INTEGER currentTime;
    LARGE_INTEGER startTime;
    bool exceededBudget = false;
    bool processingTooLong = false;
    double elapsedSec;

    QueryPerformanceCounter(&currentTime);
    EnterCriticalSection(&g_timerCriticalSection);

    // Compute delta time since last update
    LARGE_INTEGER delta;
    delta.LowPart = currentTime.LowPart - g_lastPerformanceCounterLow.LowPart;
    delta.HighPart = currentTime.HighPart - g_lastPerformanceCounterHigh.HighPart;
    if (currentTime.LowPart < g_lastPerformanceCounterLow.LowPart)
        delta.HighPart--; // Borrow

    // Convert delta to seconds (using double to avoid precision issues)
    // The decompiled code uses float10 (long double), but double is sufficient.
    long long deltaLongLong = (long long)delta.HighPart << 32 | delta.LowPart;
    double deltaSec = (double)deltaLongLong * g_qpcToSeconds;

    // Apply time scale if counter > 0x1ff (e.g., when game is paused/slowed)
    if (g_timerCounter > 0x1ff)
        deltaSec *= g_timerTimeScale;

    // Update last performance counter for next frame
    g_lastPerformanceCounterLow = currentTime;
    g_lastPerformanceCounterHigh = currentTime;

    // Begin timer processing
    TimerNode* node = g_timerListHead;
    startTime = currentTime;

    while (node != nullptr)
    {
        TimerNode* currentNode = node; // iVar5 = *piVar6; Dereference to get node address
        // (Note: piVar6 in decompiled code is actually pointed to the node itself,
        //  but the initial assignment suggests head pointer. We'll treat node as pointer)

        // Decrement remaining time
        currentNode->remainingTime -= deltaSec;
        float newRemaining = currentNode->remainingTime;

        // Check if timer expired and should fire
        bool shouldFire = false;
        if (!exceededBudget && newRemaining < 0.0f && !currentNode->paused)
            shouldFire = true;
        else if (g_disableTimerLimit) // Global override
            shouldFire = true;

        if (shouldFire)
        {
            // Fire timer callbacks
            timerTimerExpired();
            timerHandleTimeOut();

            // Check if we've spent too much time processing timers
            LARGE_INTEGER afterTime;
            QueryPerformanceCounter(&afterTime);
            long long procDeltaHigh = afterTime.HighPart - startTime.HighPart;
            unsigned int procDeltaLow = afterTime.LowPart - startTime.LowPart;
            if (afterTime.LowPart < startTime.LowPart)
                procDeltaHigh--;

            long long procDelta = ((long long)procDeltaHigh << 32) | procDeltaLow;
            double procSec = (double)procDelta * g_limitCheckToSeconds;

            if (procSec <= (double)maxFrameTime)
                exceededBudget = false;
            else
                exceededBudget = true; // Exceeded budget, stop firing more timers this frame
        }

        // Move to next node
        node = currentNode->next; // piVar6 = piVar6[1]
    }

    LeaveCriticalSection(&g_timerCriticalSection);
}