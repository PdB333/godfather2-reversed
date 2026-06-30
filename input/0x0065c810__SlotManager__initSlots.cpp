// FUNC_NAME: SlotManager::initSlots

void SlotManager::initSlots(int *thisPtr)
{
    uint randVal;
    int slotCount;

    // Initialize random number generator (seed or reset)
    randomInit();
    // Get a random value
    randVal = randomGet();
    // Compute number of slots: (random % 261) * 2 + 255
    // Range: 255 to 775 slots, odd numbers (since 255*2+255=765, etc.)
    slotCount = (randVal % 0x105) * 2 + 0xff;
    // Store slot count at offset +0x04
    thisPtr[1] = slotCount;
    // Allocate memory for slot array (each slot = 4 bytes)
    int *slotArray = (int *)allocateMemory(slotCount * 4);
    // Store pointer to array at offset +0x00
    thisPtr[0] = (int)slotArray;
    // Initialize all slots to 0
    for (uint i = 0; i < (uint)slotCount; i++)
    {
        slotArray[i] = 0;
    }
}