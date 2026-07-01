// FUNC_NAME: TaskTracker::areAllTasksDone
// Function at 0x0084a670: checks if the number of completed tasks (returning 0 from isTaskDone) matches an expected count stored in a referenced integer.
// Structure layout:
//   struct TaskTracker {
//       int*   m_pExpectedCount;       // +0x00: pointer to an integer holding the expected number of completed tasks
//       int    m_nCount;               // +0x08: number of tasks to check
//   };

bool __fastcall TaskTracker::areAllTasksDone(TaskTracker* this); // fastcall: ecx = this, edx unused

bool __fastcall TaskTracker::areAllTasksDone(TaskTracker* this)
{
    int completedCount = 0;
    unsigned int i = 0;

    if (this->m_nCount != 0) {
        do {
            int status = isTaskDone(); // returns 0 if task is done (global helper, see FUN_006b4860)
            if (status == 0) {
                completedCount++;
            }
            i++;
        } while (i < (unsigned int)this->m_nCount);
    }

    return completedCount == *(this->m_pExpectedCount + 1); // compares count of done tasks to expected count (stored at pExpectedCount+4)
}