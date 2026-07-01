// FUNC_NAME: SlotManager::findFreeSlot
uint SlotManager::findFreeSlot()
{
    // +0x04: pointer to slot array; if null, manager not initialized
    if (m_pSlotArray == 0)
        return 0x6F; // max slot count (111), meaning no free slot

    for (uint i = 0; i < 0x6F; i++)
    {
        // Get slot object by index (FUN_0077be60)
        void* slot = getSlotByIndex(i);
        // Check if slot is free (FUN_004d4b70 returns 0 when free)
        if (isSlotFree(slot) == 0)
            return i;
    }
    return 0x6F; // no free slot found
}