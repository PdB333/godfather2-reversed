// FUNC_NAME: jobProcessingThread

// Job slot structure (6 ints = 24 bytes per slot)
struct JobSlot {
    volatile int state;          // +0x00: 0=idle, 1=running? 2=ready, 3=processing, 4=done
    volatile int resultHandle;   // +0x04: result resource handle after execution
    int unknown;                 // +0x08: unused?
    int param2;                  // +0x0C: second argument to job function
    int param1;                  // +0x10: first argument to job function
    int param3;                  // +0x14: third argument to job function
};

// Globals
extern volatile JobSlot g_jobSlots[128];              // DAT_01222574 (size estimated)
extern volatile int g_jobCounter;                     // DAT_01222570 pending jobs count
extern volatile bool g_shutdownRequested;             // DAT_01222528 shutdown flag
extern void* g_jobMutex;                              // DAT_00e2ac20 mutex object
extern volatile LARGE_INTEGER g_lastPerformanceCount; // DAT_01205930/34 low/high part
extern volatile LARGE_INTEGER g_totalPerformanceCount;// DAT_01205938/3c low/high part

// Forward declarations
void mutexLock(void* mutex);                // FUN_00ab5130
void mutexUnlock(void* mutex);              // FUN_00ab4db0
void threadSignal(int signal);              // FUN_00ab51e0 (1 = job done)
void threadUnlock();                        // FUN_00ab4e70
int executeJob(int arg1, int arg2, int arg3);// FUN_00614f80

void jobProcessingThread(void)
{
    do {
        mutexLock(&g_jobMutex);                     // Enter critical section
        mutexUnlock(&g_jobMutex);                   // Release ? (double lock/unlock pattern)

        JobSlot* slot = nullptr;
        int index = 0;
        JobSlot* iter = g_jobSlots;

        // Scan for a job with state == 2 (ready to execute)
        while (iter < &g_jobSlots[128]) {           // Loop until end of array
            if (iter->state == 2) {
                slot = iter;                        // Found a ready job
                slot->state = 3;                    // Mark as processing
                break;
            }
            ++iter;                                 // Move to next slot (6 ints offset via pointer arith)
            ++index;
        }

        threadUnlock();                             // Leave quick lock

        if (slot == nullptr) {
            // No ready job – check shutdown flag
            if (g_shutdownRequested) {
                return 0;                           // Exit thread
            }
        } else {
            // Execute the job (arguments order: param1, param2, param3)
            int result = executeJob(slot->param1, slot->param2, slot->param3);
            slot->resultHandle = result;

            mutexUnlock(&g_jobMutex);               // Re-acquire to finalize
            slot->state = 4;                        // Mark as done
            threadSignal(1);                        // Signal completion to main thread

            g_jobCounter--;                         // Decrement pending count

            // Update performance counter when no pending jobs remain
            if (g_jobCounter == 0) {
                LARGE_INTEGER now;
                QueryPerformanceCounter(&now);

                // 64-bit addition with carry (low part)
                unsigned __int64 delta = (unsigned __int64)now.QuadPart - g_lastPerformanceCount.QuadPart;
                g_totalPerformanceCount.QuadPart += delta;
            }

            threadUnlock();                         // Release final lock
        }
    } while (true);
}