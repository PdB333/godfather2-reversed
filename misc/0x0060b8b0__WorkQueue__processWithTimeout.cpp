// FUNC_NAME: WorkQueue::processWithTimeout

void WorkQueue::processWithTimeout(float timeoutMs)
{
    // Global count of work items? (DAT_01205850)
    // Array of work item pointers (DAT_011da8ec) and a secondary array (DAT_011da8f0)
    // Critical section protecting the queue (DAT_012224c0)
    // Pointer to some vtable or global function table (DAT_01205868) used for calling cleanup

    LARGE_INTEGER startTime, currentTime;
    QueryPerformanceCounter(&startTime);

    EnterCriticalSection((LPCRITICAL_SECTION)&g_workQueueCriticalSection);

    int i = 0;
    if (g_numWorkItems < 1)
        goto done;

    do {
        int originalCount = g_numWorkItems;

        // Check if the item at the last index has its "valid" flag (offset +0x1d) cleared (meaning pending removal)
        if (*(char*)(*(int*)(&g_workItemList + g_numWorkItems * 4) + 0x1d) == 0) {
            // Flag is zero: item should be removed
            int* itemPtr = *(int**)(&g_workItemList + g_numWorkItems * 4);
            g_numWorkItems = g_numWorkItems - 1;

            // Call cleanup function (offset 0x10 and 0x18 in item struct)
            FUN_0060b3b0(itemPtr[4], itemPtr[6]);

            if (*itemPtr != 0) {
                // Call a virtual function? Uses vtable at *g_globalVTable + 4
                (**(code**)(*g_globalVTable + 4))(itemPtr[4], itemPtr[5]);
                itemPtr[4] = 0;
                *(char*)(itemPtr + 7) = 1; // Mark as destroyed? offset +0x1c? Actually itemPtr+7 is offset 0x1c (28)
            }

            // Check the swapped item (from secondary array at same index) for flag at offset +0x1c
            if (*(char*)((&g_workItemSwapList)[g_numWorkItems] + 0x1c) == 0) {
                g_numWorkItems = g_numWorkItems + 1; // Restore? This seems like a swap/compaction logic
                goto done;
            }
        }
        else {
            // Item is still valid: find a spot earlier in the list with a removed item and swap
            for (; i < g_numWorkItems; i++) {
                int swappedItemPtr = (&g_workItemSwapList)[i];
                if (*(char*)(swappedItemPtr + 0x1d) == 0) { // Also check removal flag
                    // Perform swap: move the last valid item to the empty slot
                    (&g_workItemSwapList)[i] = *(int*)(&g_workItemList + originalCount * 4);
                    *(int*)(&g_workItemList + originalCount * 4) = swappedItemPtr;
                    break;
                }
            }
        }

        // Timeout check
        QueryPerformanceCounter(&currentTime);
        __int64 elapsedTicks = (currentTime.HighPart - startTime.HighPart) * 0x100000000LL + (currentTime.LowPart - startTime.LowPart);
        double elapsedMs = (double)(elapsedTicks & 0x7FFFFFFFFFFFFFFF) * *(double*)&g_performanceCounterToMs;

        if (timeoutMs < elapsedMs)
            goto done; // Timeout reached

        if (g_numWorkItems <= i)
            goto done; // Processed all items

    } while (true);

done:
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_workQueueCriticalSection);
}