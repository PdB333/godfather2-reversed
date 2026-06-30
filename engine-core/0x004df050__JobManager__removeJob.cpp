// FUNC_NAME: JobManager::removeJob
// Function at 0x004df050: Removes a job/task by ID from the manager's active or pending list.
// The manager has a global singleton with an ID. The job list contains a current job (stack) and a pending list (array).
// If the current job matches, it pops from the stack; if the stack is empty, it clears it.
// If not current, it searches the pending list and removes the entry.

// Forward declarations of internal functions (assumed to be part of JobManager or global)
extern int* JobManager__getManager(); // FUN_004e0d30 - returns pointer to manager singleton
extern void JobManager__lock();       // FUN_004e0c20 - lock
extern int* JobManager__getJobList(); // FUN_004e0f60 - returns pointer to job list structure
extern void JobManager__freeStack();  // FUN_004df150 - frees the stack structure
extern void JobManager__unlock();     // FUN_004e0a20 - unlock
extern void JobManager__removeFromPendingList(); // FUN_004e14d0 - removes from pending list

// Returns 1 if job was removed, 0 if manager ID mismatch.
int JobManager::removeJob(int jobId)
{
    int* pManager = JobManager__getManager();
    int managerId = (pManager != nullptr) ? *pManager : 0; // +0x00: manager ID

    if (managerId != jobId) {
        return 0; // This manager does not handle this job ID
    }

    JobManager__lock();

    int* pJobList = JobManager__getJobList(); // +0x00: current job ID, +0x04: pointer to stack or pending list
    if (pJobList != nullptr) {
        if (*pJobList == jobId) {
            // Current job matches: handle stack
            int* pStack = (int*)pJobList[1]; // +0x04: pointer to stack structure
            if (pStack != nullptr) {
                if (pStack[1] != 0) { // +0x04: stack count
                    // Pop from stack: set current job to the top of stack
                    // Stack structure: +0x00 = pointer to array of ints, +0x04 = count
                    *pJobList = *(int*)(*pStack + (pStack[1] - 1) * 4); // array[count-1]
                    pStack[1] = pStack[1] - 1; // decrement count
                    JobManager__unlock();
                    return 1;
                }
                // Stack is empty: free it
                if (pStack != nullptr) {
                    JobManager__freeStack();
                    pJobList[1] = 0; // clear pointer
                }
            }
            JobManager__unlock();
            return 1;
        }
        else {
            // Not current job: search pending list
            int* pPendingList = (int*)pJobList[1]; // +0x04: pointer to pending list structure
            if (pPendingList != nullptr) {
                int count = pPendingList[1]; // +0x04: number of pending jobs
                if (count > 0) {
                    int* pArray = (int*)*pPendingList; // +0x00: pointer to array of job IDs
                    int* pEnd = pArray + count; // point past the end
                    while (true) {
                        pEnd--;
                        count--;
                        if (*pEnd == jobId) {
                            break; // found
                        }
                        if (count < 1) {
                            JobManager__unlock();
                            return 1; // not found
                        }
                    }
                    // Found: remove from pending list
                    JobManager__removeFromPendingList();
                }
            }
            JobManager__unlock();
            return 1;
        }
    }
    JobManager__unlock();
    return 1;
}