// FUNC_NAME: JobQueue::workerThreadMainLoop

#include <windows.h>

// Job slot structure (24 bytes each)
struct JobSlot {
    int status;                 // +0x00: 0=empty? 1=? 2=pending, 3=processing, 4=done
    int result;                 // +0x04: result of the job
    int unused;                 // +0x08: maybe padding or flags
    int param1;                 // +0x0C: first argument to job function
    int param2;                 // +0x10: second argument
    int param3;                 // +0x14: third argument
};

// Global arrays (defined elsewhere)
extern CRITICAL_SECTION g_jobCriticalSection;      // DAT_00e2ac20
extern JobSlot g_jobSlots[157];                    // DAT_01222574 (0x122312c - 0x01222574 = 0xEB8 bytes)
extern bool g_bExitRequested;                      // DAT_01222528 (byte)
extern int g_pendingJobCount;                      // DAT_01222570
extern LARGE_INTEGER g_lastTimer;                  // low part DAT_01205930, high part DAT_01205934
extern LARGE_INTEGER g_totalElapsed;               // low _DAT_01205938, high _DAT_0120593c

// External helper functions (likely from a custom synchronization layer)
void EnterCriticalSection(CRITICAL_SECTION* cs);   // FUN_00ab5130
void LeaveCriticalSection(CRITICAL_SECTION* cs);   // FUN_00ab4db0
void WaitForSingleObjectCustom();                  // FUN_00ab4e70 (could be a wait)
void ReleaseSemaphoreCustom(int count);            // FUN_00ab51e0 (+1)
int ExecuteJobFunction(int a, int b, int c);       // FUN_00614f80

// Worker thread main loop
int JobQueue::workerThreadMainLoop() {
    while (true) {
        // Acquire lock
        EnterCriticalSection(&g_jobCriticalSection);
        LeaveCriticalSection(&g_jobCriticalSection); // note: immediate release? Actually code calls Leave before processing? Stange order.

        // Search for a pending job (status == 2)
        JobSlot* foundSlot = NULL;
        int slotIndex = 0;
        JobSlot* currentSlot = g_jobSlots;
        JobSlot* endSlot = g_jobSlots + 157;
        while (currentSlot < endSlot) {
            if (currentSlot->status == 2) {          // Pending
                foundSlot = currentSlot;
                foundSlot->status = 3;               // Mark as processing
                break;
            }
            currentSlot++;
            slotIndex++;
        }

        WaitForSingleObjectCustom(); // Possibly a small yield or event wait

        if (foundSlot == NULL) {
            if (g_bExitRequested) {
                return 0; // Exit thread
            }
            // No job found, loop again (busy-wait? but maybe the wait call is a yield)
            continue;
        }

        // We have a job: execute it
        // call the job function with parameters from slot (order: param2, param1, param3)
        int jobResult = ExecuteJobFunction(foundSlot->param2, foundSlot->param1, foundSlot->param3);
        foundSlot->result = jobResult;

        // Re-acquire lock to store results
        LeaveCriticalSection(&g_jobCriticalSection);
        foundSlot->status = 4; // Mark as done

        ReleaseSemaphoreCustom(1); // Signal that a job is done (semaphore +1)

        g_pendingJobCount--;
        if (g_pendingJobCount == 0) {
            // Update global elapsed time using high-resolution counter
            LARGE_INTEGER currentTime;
            QueryPerformanceCounter(&currentTime);
            // 64-bit subtraction with carry
            unsigned int lowDiff = currentTime.LowPart - g_lastTimer.LowPart;
            unsigned int highDiff = currentTime.HighPart - g_lastTimer.HighPart - (lowDiff > currentTime.LowPart ? 1 : 0);
            // Add to total elapsed (64-bit)
            g_totalElapsed.LowPart += lowDiff;
            g_totalElapsed.HighPart += highDiff + (g_totalElapsed.LowPart < lowDiff ? 1 : 0);
        }

        WaitForSingleObjectCustom(); // Another yield? or release lock? Actually code calls FUN_00ab4e70 after decrement.
        // The original code calls FUN_00ab4e70 again at the end of the else block.
        // This might be a custom small delay to avoid busy-wait.
    }
}