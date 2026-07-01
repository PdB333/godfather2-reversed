// FUNC_NAME: PlayerTaskManager::clearAllTasks

void __fastcall PlayerTaskManager::clearAllTasks(void)
{
    // Array of 8 task slots at offset +0x75c
    // Each slot is 8 bytes: pointer to a task object + unknown data
    int slotIndex = 8;
    int *slotBase = (int *)((int)this + 0x75c);

    // Iterate over all 8 slots
    do
    {
        if (*slotBase != 0)
        {
            // Destroy or release the task object in this slot
            destroyTaskSlot(slotBase);
            *slotBase = 0; // Clear the pointer
        }
        slotBase += 2; // Move to next slot (8 bytes per entry)
        slotIndex--;
    } while (slotIndex != 0);

    // Clear bit 4 of the flags at +0x81c (e.g., mark as "no active tasks")
    *(unsigned int *)((int)this + 0x81c) &= 0xFFFFFFEF;

    // Reset the task slot array (e.g., reinitalize the list)
    clearTaskSlotArray(this, (int *)((int)this + 0x75c), 8);

    // Restore default state for current task type and next task index
    *(int *)((int)this + 0x79c) = DAT_00d5ccf8;  // Default task type (global)
    *(int *)((int)this + 0x7a0) = 0;              // Next task index
}