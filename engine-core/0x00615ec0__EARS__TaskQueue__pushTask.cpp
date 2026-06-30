// FUNC_NAME: EARS::TaskQueue::pushTask
// Address: 0x00615ec0
// Role: Push a work item onto the global task queue. Fast path (stack-based) for main thread; slow path uses a free list with a custom allocator (FUN_00485280) for other threads.

// Known structures:
// WorkItem {
//     void* callback;    // +0x00
//     uint32_t context;  // +0x04
//     uint32_t flags;    // +0x08
//     WorkItem* next;    // +0x0C
// }
// 
// Global queue pointers:
// WorkItem* g_freeWorkItemHead; // PTR_DAT_01117bb0
// WorkItem* g_workQueueHead;    // DAT_01117bbc
// WorkItem* g_workQueueTail;    // DAT_01117bc0
// uint8_t* g_mainThreadStack;   // DAT_01206880 (some thread-local bump allocator context)

// The condition checks if we are running on the main thread via a flag inside the thread-local storage (fs:[0x2C])
// FUN_00485280 is an internal function that allocates new WorkItems from the system heap and adds them to the free list.

void EARS::TaskQueue::pushTask(uint32_t param_1)
{
    uint32_t* puVar1;
    uint32_t* puVar2;
    int unaff_FS_OFFSET;

    // Check main thread flag
    if (*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x34) == 0)
    {
        // Fast path: allocate from main thread stack
        puVar1 = (uint32_t *)(g_mainThreadStack + 0x14);
        *(uint32_t **)(g_mainThreadStack + 0x14) = &PTR_LAB_01127730; // store a sentinel/return address
        *puVar1 = *puVar1 + 4;
        puVar2 = (uint32_t *)((*puVar1 + 3) & 0xfffffffc);
        *puVar1 = (uint32_t)puVar2;
        *puVar2 = param_1; // store context
        *puVar1 = *puVar1 + 4;
        return;
    }

    // Slow path: obtain a free WorkItem from the global free list
    WorkItem* item = (WorkItem*)g_freeWorkItemHead;
    if (g_freeWorkItemHead == (WorkItem*)0x0)
    {
        do {
            FUN_00485280(); // internally allocates new items from heap
            item = g_freeWorkItemHead;
        } while (g_freeWorkItemHead == (WorkItem*)0x0);
    }

    // Remove from free list
    g_freeWorkItemHead = (WorkItem*)item->next;
    item->next = nullptr;

    // Initialize work item
    item->callback = &LAB_00615e40; // placeholder callback (likely a stub that returns to caller)
    item->context = param_1;
    item->flags = 0;

    // Enqueue to global work queue
    if (g_workQueueTail != nullptr)
    {
        g_workQueueTail->next = item;
        g_workQueueTail = item;
    }
    else
    {
        g_workQueueHead = item;
        g_workQueueTail = item;
    }
}