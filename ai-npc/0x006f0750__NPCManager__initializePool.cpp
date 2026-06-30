// FUNC_NAME: NPCManager::initializePool
// Function at 0x006f0750 - Initializes an internal pool of 100 slots (each 0x2c bytes) and then copies a head pointer to tail.
void __fastcall NPCManager::initializePool(void* thisPtr)
{
    // Step through 100 pool slots (0x1130 / 0x2c = 100)
    for (int slotOffset = 0; slotOffset < 0x1130; slotOffset += 0x2c)
    {
        // Call helper to initialize/clear each slot (probably sets up a free list or default state)
        FUN_006f5320();
    }
    // After all slots are initialized, copy the head of the free list (or similar) to the tail pointer
    // +0x18: likely head pointer (start of free list)
    // +0x1c: likely tail pointer (end of free list)
    *(int*)((char*)thisPtr + 0x1c) = *(int*)((char*)thisPtr + 0x18);
}