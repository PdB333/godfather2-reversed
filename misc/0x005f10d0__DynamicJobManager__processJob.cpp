// FUNC_NAME: DynamicJobManager::processJob
// Address: 0x005f10d0
// Role: Processes the highest priority job from the global job list, then either executes it or reinserts it into a per-priority queue.

#include <cstdint>

// Forward declarations
class DynamicJobManager;
struct JobNode;

// Global data (static members of DynamicJobManager)
extern JobNode* g_pJobListHead;          // DAT_011a0ec0
extern int32_t g_iCurrentPriority;       // DAT_011a0ee4 (0-8)
extern JobNode* g_pFreeListHead;         // DAT_011a0ed8
extern int32_t g_iFreeListCount;         // DAT_011a0edc
extern void* g_pVTable;                  // DAT_01223510 (some vtable)

// Per-priority queue structure (0xC bytes each)
struct PriorityQueue {
    JobNode* head;   // +0x00
    JobNode* tail;   // +0x04
    uint16_t count;  // +0x08
    uint16_t max;    // +0x0A
};
extern PriorityQueue g_priorityQueues[9]; // Array of 9 queues (indices 0-8)

// Job node structure (size unknown, but at least 0x2C bytes)
struct JobNode {
    JobNode* next;           // +0x00
    uint32_t flags;          // +0x04 (bit 0x10 = "in use"?)
    uint16_t field_0x08;     // +0x08
    uint16_t field_0x0A;     // +0x0A
    uint32_t field_0x0C;     // +0x0C
    uint32_t field_0x10;     // +0x10
    uint32_t field_0x14;     // +0x14
    uint32_t field_0x18;     // +0x18
    uint32_t field_0x1C;     // +0x1C
    uint8_t priority;        // +0x1E (used for selection)
    uint32_t callback;       // +0x20 (function pointer)
    uint32_t param1;         // +0x24
    uint32_t param2;         // +0x28
    uint32_t param3;         // +0x2C
};

// External functions
void FUN_005dbc10(); // Likely "JobManager::notify" or similar
void FUN_005f16b0(); // Likely "JobManager::processNext" or "schedule"
void FUN_005f57b0(); // Likely "JobManager::executeCallback"

// The function
JobNode* DynamicJobManager::processJob()
{
    JobNode* pSelectedJob = nullptr;
    bool bExecuted = false;

    // Only process if current priority < 9 (valid range)
    if (g_iCurrentPriority < 9)
    {
        uint8_t bestPriority = *(uint8_t*)((uint8_t*)this + 0x1C); // this->priorityThreshold? Actually offset 0x1C from this
        JobNode* pPrev = nullptr;
        JobNode* pCurr = g_pJobListHead;

        // Scan global job list for the highest priority (lowest value) job that matches our criteria
        while (pCurr != nullptr)
        {
            // Check: job's type (offset 0x28) must match this->field_0x14 (offset 0x14 from this)
            // and job must not have flag 0x10 set (in use?)
            if ((*(int32_t*)((uint8_t*)this + 0x14) != *(int32_t*)((uint8_t*)pCurr + 0x28)) &&
                ((*(uint8_t*)((uint8_t*)pCurr + 0x04) & 0x10) == 0) &&
                (*(uint8_t*)((uint8_t*)pCurr + 0x1E) <= bestPriority))
            {
                pSelectedJob = pPrev; // Actually pPrev is the previous node? The code sets puVar9 = puVar8 (previous selected) then updates puVar8 = pCurr. So pSelectedJob becomes the previous best? Wait, the decompiler logic: puVar9 = puVar8; then if condition, puVar8 = puVar6; puVar9 = puVar6; So puVar9 ends up being the current node if condition true. So pSelectedJob = pCurr.
                pPrev = pCurr;
                bestPriority = *(uint8_t*)((uint8_t*)pCurr + 0x1E);
            }
            pCurr = pCurr->next;
        }

        // If a job was selected, process it
        if (pSelectedJob != nullptr)
        {
            // Call the job's callback (offset 0x24) with (this, 1)
            if (pSelectedJob->callback != 0)
            {
                ((void (*)(JobNode*, int32_t))pSelectedJob->callback)(pSelectedJob, 1);
            }

            FUN_005dbc10(); // Notify job manager

            if (g_iCurrentPriority == 0)
            {
                // Execute via vtable call (some system callback)
                (**(void (***)(void*, uint16_t))g_pVTable)((void*)((uint8_t*)pSelectedJob + 0x08), *(uint16_t*)((uint8_t*)pSelectedJob + 0x08));
                FUN_005f57b0(); // Execute callback
                bExecuted = true;
            }
            else
            {
                FUN_005f16b0(); // Schedule next
                pSelectedJob = nullptr; // Mark as not selected for insertion
            }
        }
    }

    // If there are free jobs in the free list, remove one
    if ((g_iCurrentPriority != 0) && (g_iFreeListCount != 0) && (g_pFreeListHead != &g_pFreeListHead))
    {
        g_iCurrentPriority--;
        pSelectedJob = g_pFreeListHead;
        g_pFreeListHead = (JobNode*)*g_pFreeListHead; // Remove from free list
    }

    // If no job was selected from free list, create a new job from this object's data
    if (pSelectedJob == nullptr)
    {
        // Call FUN_005dbc10 with parameters from this
        FUN_005dbc10(*(int32_t*)this, *(float*)((uint8_t*)this + 0x04), *(uint32_t*)((uint8_t*)this + 0x08),
                     *(uint32_t*)((uint8_t*)this + 0x14), *(uint32_t*)((uint8_t*)this + 0x18));
    }
    else
    {
        // Fill the selected job node with data from this
        int32_t priorityIndex = *(int32_t*)((uint8_t*)this + 0x08); // this->priorityIndex
        pSelectedJob->priority = *(uint8_t*)((uint8_t*)this + 0x1C);
        pSelectedJob->callback = *(uint32_t*)((uint8_t*)this + 0x10);
        pSelectedJob->param1 = *(uint32_t*)((uint8_t*)this + 0x14);
        pSelectedJob->param2 = *(uint32_t*)((uint8_t*)this + 0x18);
        uint16_t flags = *(uint16_t*)((uint8_t*)this + 0x0C);
        pSelectedJob->field_0x0C = *(uint32_t*)((uint8_t*)this + 0x08);
        pSelectedJob->field_0x10 = 0;
        *(uint8_t*)((uint8_t*)pSelectedJob + 0x1C) = 0;
        *(uint8_t*)((uint8_t*)pSelectedJob + 0x1D) = 0;
        pSelectedJob->field_0x20 = 0;
        *(uint16_t*)((uint8_t*)pSelectedJob + 0x10) = flags;
        *(uint16_t*)((uint8_t*)pSelectedJob + 0x42) = 0;

        if (bExecuted)
        {
            *(uint16_t*)((uint8_t*)pSelectedJob + 0x10) |= 2; // Set flag 0x2
        }

        // Insert into per-priority queue
        int32_t index = priorityIndex * 0xC; // Each queue entry is 0xC bytes
        if (g_priorityQueues[priorityIndex].count < g_priorityQueues[priorityIndex].max)
        {
            if (g_priorityQueues[priorityIndex].count == 0)
            {
                g_priorityQueues[priorityIndex].head = pSelectedJob;
            }
            else
            {
                if (g_priorityQueues[priorityIndex].tail == nullptr)
                {
                    return pSelectedJob; // Should not happen
                }
                g_priorityQueues[priorityIndex].tail->next = pSelectedJob;
            }
            pSelectedJob->next = nullptr;
            g_priorityQueues[priorityIndex].tail = pSelectedJob;
            g_priorityQueues[priorityIndex].count++;
            FUN_005dbc10(&g_priorityQueues[priorityIndex], g_priorityQueues[priorityIndex].count);
        }
    }

    return pSelectedJob;
}