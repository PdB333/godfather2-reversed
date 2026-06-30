// FUNC_NAME: processTask
// Function address: 0x005bf2b0
// This function appears to be part of a task/job manager. It registers a task object into a fixed-size
// active task slot table (15 slots), then repeatedly calls its update method until it returns 0 (done).
// After completion, it updates the global free slot pointer to point to the highest occupied slot
// (for future allocations). The inner update function (FUN_005bf1e0) likely returns a char status:
// 0 = finished, non-zero = continue.

// Global task slot array (15 slots, indices 0-14)
static int g_taskSlots[15]; // DAT_01205608
// Global free slot pointer: points to the next free slot above the highest occupied slot.
static int g_nextFreeSlot; // DAT_00f17914

void __fastcall processTask(int taskObject) // param_1 in ECX
{
    int i;
    int freeIndex;
    char status;

    // Find the highest occupied slot (search from index 14 down to 0)
    i = 14;
    do {
        if (g_taskSlots[i] != 0) break;
        i--;
    } while (i >= 0);

    // Set free slot index to the slot just above the highest occupied (or 0 if none)
    g_nextFreeSlot = i + 1;
    // Store the task object at that slot
    g_taskSlots[g_nextFreeSlot] = taskObject;

    // Process the task repeatedly until completion
    do {
        status = FUN_005bf1e0(taskObject); // taskObject->update() – returns 0 when done
    } while (status != 0);

    // Reset free pointer to the top and find the new highest occupied slot
    g_nextFreeSlot = 14;
    do {
        if (g_taskSlots[g_nextFreeSlot] != 0) {
            return; // There are still active tasks; leave free pointer at this index
        }
        g_nextFreeSlot--;
    } while (g_nextFreeSlot >= 0);

    // All slots are empty; free pointer remains at -1 (will become 0 on next allocation)
    return;
}