// FUNC_NAME: TaskScheduler::processLoop
// Address: 0x00495490
// This function appears to be the main processing loop of a task scheduler worker thread.
// It uses a global lock (DAT_01217d38) and processes tasks from a global queue (DAT_01217b00).
// The loop continues based on state fields in the scheduler object.

class TaskScheduler {
public:
    // +0x14 : current state (for loop condition)
    // +0x18 : target state (for loop condition)
    int m_currentState;   // +0x14
    int m_targetState;    // +0x18

    void processLoop(int savedState /* unaff_EDI */);
};

// Task structure returned from popTask (FUN_004955e0)
struct Task {
    void (*m_func)(int, int, int, int);  // +0x00
    int m_arg1;                           // +0x04
    int m_arg2;                           // +0x08
    int m_arg3;                           // +0x0C
    int m_arg4;                           // +0x10
    int m_completionFlag;                 // +0x14 (source for copy)
    int m_completionTarget;               // +0x18 (destination for copy)
};

// Global lock variable
extern volatile int g_taskLock;           // DAT_01217d38

// Global queue instance (presumably a pointer to a list or queue)
extern TaskQueue g_taskQueue;            // DAT_01217b00

// External helper functions
extern void processDeferredCleanup(int param);       // FUN_00ab51e0
extern int checkGlobalState(int *state);              // FUN_00ab5130  (returns -1 on error)
extern void handleError(int *errorState);             // FUN_00ab4b40
extern Task* popTask(TaskQueue *queue);               // FUN_004955e0

void TaskScheduler::processLoop(int savedState)
{
    do {
        // Atomically read and clear the global lock
        int lockValue = g_taskLock;
        LOCK();
        g_taskLock = 0;
        UNLOCK();

        // If a pending signal or deferred work exists, process it
        if (lockValue != 0) {
            processDeferredCleanup(lockValue);
        }

        // Check a global state; if negative, handle error
        int stateCheck = checkGlobalState(&g_taskQueue);  // DAT_00e2e234 is actually a member of the queue?
        if (stateCheck < 0) {
            handleError(&g_taskQueue);   // DAT_00e2e4b4
        } else {
            // Pop a task from the global queue
            Task *task = popTask(&g_taskQueue);  // DAT_01217b00

            // Execute the task (function pointer with four arguments)
            task->m_func(task->m_arg1, task->m_arg2, task->m_arg3, task->m_arg4);

            // After execution, atomically copy a completion flag
            LOCK();
            task->m_completionTarget = task->m_completionFlag;
            UNLOCK();
        }
    } while ((savedState != this->m_targetState) && (savedState == this->m_currentState));
    // The loop continues as long as savedState (preserved from caller) is not equal to m_targetState
    // AND savedState equals m_currentState. This suggests a state-driven spin mechanism.
}