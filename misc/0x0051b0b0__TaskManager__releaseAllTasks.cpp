// FUNC_NAME: TaskManager::releaseAllTasks
void TaskManager::releaseAllTasks(TaskManager *this)
{
    // Clear task manager flags: bits 16 and 19 (possibly "initialized" / "active" flags)
    this->managerFlags &= 0xFFF6FFFF;
    // Reset active task count and current task index
    this->activeTaskCount = 0;
    this->currentTaskIndex = 0;
    // Loop through all task slots
    int count = this->totalTaskSlots;
    if (count > 0) {
        TaskSlot *slot = this->taskSlots; // array at +0xF0
        for (int i = 0; i < count; ++i) {
            // If the slot has an allocated resource
            if (slot->resourceID != 0) {
                // Mark the slot as pending release (bit 26)
                slot->flags |= 0x4000000;
                // Call the cleanup routine for the slot's resource
                FUN_005343f0(); // Likely frees or deactivates the resource
                slot->resourceID = 0;
            }
            // Clear release-related flags (bits 27 and 28)
            slot->flags &= 0xE7FFFFFF;
            ++slot; // Advance by sizeof(TaskSlot) = 20 bytes
        }
    }
}