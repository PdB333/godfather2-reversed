// FUNC_NAME: TimerList::processTimerList
// Function at 0x0060c5e0 - Processes a linked list of timers, decrementing their remaining time.
// If a timer reaches zero (and not paused) or global flag is set, calls update functions and checks elapsed time against budget.
// High timer count (>511) slows down time multiplier.
// Uses global critical section for thread safety.

#include <windows.h>

// Forward declarations
void FUN_0060c430(); // update function 1
void FUN_0060d3f0(); // update function 2

// Timer node structure (offsets based on decompilation)
struct TimerNode {
    TimerNode* self;    // +0x00 points to itself (validation)
    TimerNode* next;    // +0x04 next node in list
    // ... other fields ...
    uint8_t flags;      // +0x29 bit0 = paused? (checked == 0 to allow trigger)
    float timeRemaining; // +0x30 seconds remaining
};

// Global variables (from Ghidra)
extern TimerNode* g_pTimerListHead; // DAT_012224e0 - head of timer list
extern int g_timerCount;            // DAT_012224e8 - number of active timers
extern CRITICAL_SECTION g_timerCriticalSection; // DAT_012224f8
extern float g_performanceFrequency; // _DAT_01163ec8 - QPC frequency divisor
extern float g_altFrequency;        // _DAT_01163ecc - alternative frequency for timeout check
extern float g_slowdownMultiplier;  // DAT_00e2e230 - applied when timer count > 511
extern int g_forceUpdateAll;        // DAT_00f15a3a - if non-zero, forces update on all timers
extern LARGE_INTEGER g_lastPerformanceCount; // _DAT_01205860 and _DAT_01205864 (split high/low)

void TimerList::processTimerList(float maxElapsedTime)
{
    LARGE_INTEGER currentCount;

    // Start timing
    QueryPerformanceCounter(&currentCount);

    // Lock the timer list
    EnterCriticalSection(&g_timerCriticalSection);

    // High and low parts for delta calculation
    unsigned long lowPart = currentCount.LowPart;
    unsigned long highPart = currentCount.HighPart;

    // Calculate delta time in QPC ticks since last frame
    unsigned __int64 deltaTicks = (currentCount.QuadPart - g_lastPerformanceCount.QuadPart);
    
    // Store current count as new last
    g_lastPerformanceCount.HighPart = currentCount.HighPart;
    g_lastPerformanceCount.LowPart = currentCount.LowPart;

    // Convert ticks to seconds (float). Use trick to handle negative delta (wraparound)
    // fStack_24 = deltaTicks * performance frequency (likely 1/freq, so multiply)
    float deltaTime = (float)deltaTicks * g_performanceFrequency;

    // If more than 511 timers, apply slowdown
    if (g_timerCount > 511) {
        deltaTime *= g_slowdownMultiplier;
    }

    bool budgetExceeded = false;

    // Iterate through the linked list
    TimerNode* pNode = g_pTimerListHead;
    while (pNode != nullptr) {
        // Subtract delta from timer
        pNode->timeRemaining -= deltaTime;

        // Check if we should trigger update functions:
        // - If budget not exceeded AND timer went negative AND not paused
        // - OR if global force flag is zero (meaning force update all)
        if (((!budgetExceeded) && (pNode->timeRemaining < 0.0f) && (pNode->flags == 0)) 
            || (g_forceUpdateAll == '\0')) 
        {
            // Call update functions
            FUN_0060c430();
            FUN_0060d3f0();

            // Measure elapsed time since start of this function
            LARGE_INTEGER afterCall;
            QueryPerformanceCounter(&afterCall);
            unsigned __int64 elapsedTicks = afterCall.QuadPart - currentCount.QuadPart;
            float elapsedSeconds = (float)elapsedTicks * g_altFrequency;

            // If elapsed time exceeds budget, set flag (prevents further triggers unless forced)
            if (elapsedSeconds > maxElapsedTime) {
                budgetExceeded = true;
            } else {
                budgetExceeded = false;
            }
        }

        // Advance to next node
        pNode = pNode->next;
    }

    LeaveCriticalSection(&g_timerCriticalSection);
}