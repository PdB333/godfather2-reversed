// FUNC_NAME: EventScheduler::processPendingEvents

#include <windows.h>

// Globals (from Ghidra, addresses approximate)
extern CRITICAL_SECTION g_timerCriticalSection;           // DAT_012224f8
extern int g_timerCount;                                  // DAT_01205854
extern int* g_timerActiveList[];                          // DAT_011e28ec (array of pointers)
extern int* g_timerSwapList[];                            // DAT_011e28f0 (secondary array)
extern void** g_timerVTable;                              // DAT_01205868 (vtable pointer for timer callback manager)
extern float g_timerTimeScale;                            // DAT_01163ecc (conversion factor)

// Forward declarations
void stopTimerCallback(int* param1, int* param2);         // FUN_0060be80

// Structure for a pending timer/callback event
struct PendingEvent {
    // +0x00: vtable pointer
    int* vtable;
    // ... other fields ...
    // +0x1C (7): callback object
    int* callbackObject;
    // +0x20 (8): callback argument
    int callbackArg;
    // +0x24 (9): some other object
    int* extraObject;
    // +0x28 (10): flag byte (offset 0x28)
    char flag28;
    // +0x29: active flag (non-zero if actively scheduled)
    char active;
    // +0x2A: padding ...
};

// EventScheduler::processPendingEvents
// Processes and removes finished/deactivated events from the timer queue.
// Uses a time limit to avoid stalling the frame.
void __cdecl EventScheduler_ProcessPendingEvents(void) {
    LARGE_INTEGER startTime;
    LARGE_INTEGER currentTime;
    int i;
    int* eventPtr;
    int tempIndex;
    int savedCount;
    int timeDelta;
    double elapsedTime;
    bool limitReached;

    QueryPerformanceCounter(&startTime);
    EnterCriticalSection(&g_timerCriticalSection);

    i = 0;
    if (g_timerCount < 1) {
        LeaveCriticalSection(&g_timerCriticalSection);
        return;
    }

    do {
        savedCount = g_timerCount;
        // Check the last event in the active list
        eventPtr = g_timerActiveList[savedCount];
        if (eventPtr->active == 0) {
            // Event is inactive: remove it from the queue
            eventPtr = g_timerActiveList[savedCount];
            g_timerCount--; // remove from active list
            stopTimerCallback(eventPtr->callbackObject, eventPtr->extraObject);
            if (eventPtr->vtable != 0) {
                // Call virtual function at index 1 (cancel/destroy)
                ((void (__thiscall*)(int*, int))(*g_timerVTable))(eventPtr->callbackObject, eventPtr->callbackArg);
                eventPtr->callbackObject = 0;
                eventPtr->flag28 = 1; // mark as properly cleaned
            }
            // Check secondary swap list at new count
            if (g_timerSwapList[g_timerCount]->flag28 == 0) {
                g_timerCount++; // readjust to avoid processing further? (bug workaround)
                goto done;
            }
        } else {
            // Event is active: scan for an inactive event to swap with the last active
            for (; i < g_timerCount; i++) {
                int* swapEvent = g_timerSwapList[i];
                if (swapEvent->active == 0) {
                    g_timerSwapList[i] = g_timerActiveList[g_timerCount];
                    g_timerActiveList[savedCount] = swapEvent;
                    break;
                }
            }
        }

        // Check if we've exceeded the time budget
        QueryPerformanceCounter(&currentTime);
        // Compute elapsed time in seconds (approximate)
        // The original uses a float conversion of the 64-bit delta multiplied by a scale factor.
        timeDelta = currentTime.LowPart - startTime.LowPart;
        __int64 delta = (__int64)((ULONGLONG)currentTime.QuadPart - (ULONGLONG)startTime.QuadPart);
        elapsedTime = (double)(delta & 0x7FFFFFFFFFFFFFFF) * (double)*(float*)&g_timerTimeScale; // simplified
        if (elapsedTime > 1.0) {
            goto done;
        }
        if (g_timerCount <= i) {
            LeaveCriticalSection(&g_timerCriticalSection);
            return;
        }
    } while (true);

done:
    LeaveCriticalSection(&g_timerCriticalSection);
    return;
}