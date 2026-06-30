// FUNC_NAME: InputDeviceManager::~InputDeviceManager
// Function at 0x00569190: Destructor for InputDeviceManager. Cleans up all controller slots and their child device pending lists.
// Sets vtable to a dummy destructor vtable to avoid virtual calls during destruction.
// Iterates over an array of controller slot managers (offset 0x228, count at offset 0x328).
// Each slot manager has an array of up to 65 device pointers (starting at slot[1], count at slot offset 0x104).
// For each device, sets a flag (offset 0x128) to 1, releases pending items in an array at offset 0x12C
// using FUN_009c8eb0, then zeros the pending count (offset 0x14C).

void __thiscall InputDeviceManager::~InputDeviceManager(void *this)
{
    // Set vtable to destructor vtable (prevent virtual calls during destruction)
    *(void **)this = (void *)&PTR_FUN_00e3aad8; // +0x00

    // Number of controller slot managers
    uint slotCount = *(uint *)((char *)this + 0x328); // +0xCA * 4

    if (slotCount != 0)
    {
        // Array of pointers to slot managers (each pointer = 4 bytes)
        int **slotManagers = (int **)((char *)this + 0x228); // +0x8A * 4

        for (uint slotIdx = 0; slotIdx < slotCount; ++slotIdx)
        {
            int *slotMgr = slotManagers[slotIdx];
            if (slotMgr != 0)
            {
                // Count of active devices in this slot manager (stored at offset 0x104)
                uint deviceCount = (uint)slotMgr[0x41]; // offset 0x41 * 4 = 0x104

                if (deviceCount != 0)
                {
                    // Devices are stored as an array of pointers starting at slotMgr[1] (skipping the first element)
                    // This loop processes slotMgr[1] through slotMgr[deviceCount]
                    for (uint devIdx = 0; devIdx < deviceCount; ++devIdx)
                    {
                        int *device = (int *)(slotMgr[devIdx + 1]);

                        // Mark device as being destroyed (byte at offset 0x128)
                        *(char *)((char *)device + 0x128) = 1;

                        // If there are pending items (count at offset 0x14C)
                        uint pendingCount = *(uint *)((char *)device + 0x14C); // +0x14C
                        if (pendingCount != 0)
                        {
                            // Array of pending handles at offset 0x12C (300 decimal)
                            int *pendingArray = (int *)((char *)device + 300); // +0x12C
                            for (uint i = 0; i < pendingCount; ++i)
                            {
                                FUN_009c8eb0(pendingArray[i]); // Release each item
                            }
                        }
                        // Clear the pending count
                        *(uint *)((char *)device + 0x14C) = 0;
                    }
                }
            }
        }
    }
}