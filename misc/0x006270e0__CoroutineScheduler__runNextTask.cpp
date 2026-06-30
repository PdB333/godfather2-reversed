// FUNC_NAME: CoroutineScheduler::runNextTask

// Function at 0x006270e0 - Core coroutine scheduler loop
// This function manages a coroutine context (fiber) that processes a queue of tasks.
// It uses a stack pointer (+0x08), a manager object (+0x10), and an active flag (+0x31).
// Tasks are stored as linked list nodes; each task has a type (7) and associated data.
// The function picks tasks from the list, sets up execution context, calls the task executor,
// and repeats until the queue is empty.

void CoroutineScheduler::runNextTask()
{
    // Save the current active flag (byte at this+0x31)
    uint8_t savedActiveFlag = *(uint8_t *)(this + 0x31);
    
    // Advance stack pointer by 8 bytes (simulate pushing a frame)
    *(int32_t *)(this + 0x08) += 8;
    
    // Clear the active flag to indicate we are now running
    *(uint8_t *)(this + 0x31) = 0;
    
    // Check if the task queue is empty (manager->taskListHead at +0x14)
    if (*(int32_t *)(*(int32_t *)(this + 0x10) + 0x14) == 0)
    {
        // Queue empty: restore flag and stack pointer, then return (yield)
        *(uint8_t *)(this + 0x31) = savedActiveFlag;
        *(int32_t *)(this + 0x08) -= 8;
        return;
    }
    
    do
    {
        // Remove the first task node from the queue (manager->taskListHead)
        CoroutineTask *taskNode = *(CoroutineTask **)(*(int32_t *)(this + 0x10) + 0x14);
        *(int32_t *)(*(int32_t *)(this + 0x10) + 0x14) = *(int32_t *)taskNode;  // Update head to next
        
        // Insert the node at the head of the free list (manager->freeListHead at +0x10)
        *(int32_t *)taskNode = *(int32_t *)(*(int32_t *)(this + 0x10) + 0x10);
        *(int32_t *)(*(int32_t *)(this + 0x10) + 0x10) = (int32_t)taskNode;
        
        // Set up a stack frame for this task: push type 7 and the task pointer
        int32_t *stackPtr = *(int32_t **)(this + 0x08);
        *(int32_t *)(stackPtr - 2) = 7;                             // Task type
        *(int32_t **)(stackPtr - 1) = taskNode;                     // Task pointer
        
        // Mark task as ready (clear lower 2 bits of byte at +0x05)
        taskNode->flags1 &= 0xFC;  // bit0 and bit1 cleared
        
        // Check if this task has already been processed (bit2 of byte at +0x06 set)
        CoroutineManager *mgr = *(CoroutineManager **)(this + 0x10);
        if ((*(uint8_t *)(taskNode->field_0x06) & 4) == 0)
        {
            // Look up the task's data in a hash table (manager->dataHash +0x5c)
            int32_t tablePtr = *(int32_t *)(*(int32_t *)(this + 0x10) + 0x5c);
            int32_t *entryArray = (int32_t *)(*(int32_t *)(taskNode + 0x10) +
                ((1 << (*(uint8_t *)(taskNode + 0x07) & 0x1F)) - 1) & *(uint32_t *)(tablePtr + 8));
            
            int32_t *foundEntry = nullptr;
            do
            {
                if ((*entryArray == 4) && (*(entryArray + 1) == tablePtr))
                {
                    foundEntry = entryArray + 2;  // Points to the real data (two ints)
                    if (*(entryArray + 2) != 0)
                        break;
                }
                entryArray = (int32_t *)*(entryArray + 4);  // Follow next pointer in hash chain
            } while (entryArray != nullptr);
            
            if (foundEntry == nullptr)
            {
                // No matching entry: mark task as processed (set bit2)
                *(uint8_t *)(taskNode + 0x06) |= 4;
            }
        }
        
        int32_t *dataPtr = nullptr;   // piVar6
        if (foundEntry != nullptr)
        {
            dataPtr = foundEntry;
        }
        
        // If we have data, push it onto the stack and call the task executor
        if (dataPtr != nullptr)
        {
            int32_t *currentStack = *(int32_t **)(this + 0x08);
            *currentStack = *dataPtr;
            *(currentStack + 1) = *(dataPtr + 1);
            
            // Update stack pointer and set task info
            int32_t *newStack = *(int32_t **)(this + 0x08);
            *(int32_t **)(newStack + 3) = taskNode;   // +0x0C: task node
            *(int32_t *)(newStack + 2) = 7;          // +0x08: type
            *(int32_t *)(this + 0x08) += 0x10;       // Advance stack by 16 bytes
            
            // Call the actual task execution function (likely an inline or virtual)
            CoroutineExecutor::execute();   // This is FUN_006362d0
        }
        
        // Check again if the queue is empty
        if (*(int32_t *)(*(int32_t *)(this + 0x10) + 0x14) == 0)
        {
            // Restore flag and stack pointer, then return
            *(int32_t *)(this + 0x08) -= 8;
            *(uint8_t *)(this + 0x31) = savedActiveFlag;
            return;
        }
    } while (true);
}

// Supporting structures (guessed offsets)
struct CoroutineManager
{
    /* +0x00 */ uint32_t unknown0;
    /* +0x04 */ uint32_t unknown4;
    /* +0x08 */ uint32_t unknown8;
    /* +0x0C */ uint32_t unknownC;
    /* +0x10 */ CoroutineTask *freeListHead;   // Free list of tasks
    /* +0x14 */ CoroutineTask *taskListHead;   // Active task queue
    /* +0x5C */ void *dataHashTable;           // Hash table for task data
};

struct CoroutineTask
{
    /* +0x00 */ CoroutineTask *next;           // Linked list pointer
    /* +0x04 */ uint32_t field_0x04;
    /* +0x05 */ uint8_t flags1;
    /* +0x06 */ uint8_t flags2;
    /* +0x07 */ uint8_t field_0x07;            // Used for hash
    /* +0x10 */ void *somePointer;
};