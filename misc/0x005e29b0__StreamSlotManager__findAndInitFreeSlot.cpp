// FUNC_NAME: StreamSlotManager::findAndInitFreeSlot
int __fastcall StreamSlotManager::findAndInitFreeSlot(void* unusedThis, StreamSlotManager* manager)
{
    // manager is a pointer to the StreamSlotManager instance (passed in edx)
    // Manager layout: 
    //   +0x000: largeSlots[5] (each 0x4a4 bytes) - main slot data
    //   +0x488: smallSlots[5] (each 0x129 bytes) - status/info structs
    // Small slot struct first int at offset 0 is a state field; value 3 = free

    for (int i = 0; i < 5; i++)
    {
        int* statusField = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(manager) + 0x488 + i * 0x129);
        if (*statusField == 3)   // slot is free
        {
            uintptr_t largeSlotBase = reinterpret_cast<uintptr_t>(manager) + i * 0x4a4;

            // +0x26c in large slot: some handle/resource ID
            uint32_t handle = *reinterpret_cast<uint32_t*>(largeSlotBase + 0x26c);
            FUN_005dbc10(handle);   // release or cleanup resource

            FUN_005e9440();         // reset global state?
            FUN_005e86e0();         // reinitialize step 1
            FUN_005e86e0();         // reinitialize step 2

            // Clear two fields at +0x200 and +0x204 in large slot
            *reinterpret_cast<uint32_t*>(largeSlotBase + 0x200) = 0;
            *reinterpret_cast<uint32_t*>(largeSlotBase + 0x204) = 0;

            return i;   // return found slot index
        }
    }
    return -1;   // no free slot
}