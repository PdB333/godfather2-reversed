// FUNC_NAME: EntityManager::areAllEntitiesValid
// Address: 0x005ef080
// Role: Checks if all entity slots (128 main, plus 3 arrays of 5, plus 4 separate) are active/valid.

bool __fastcall EntityManager::areAllEntitiesValid(int thisPtr)
{
    bool allValid = true;
    int slotBase;
    int i;

    // Check the main array of 128 slots starting at offset 0x65C, each slot size 0xF8
    slotBase = thisPtr + 0x65C;
    for (i = 0; i < 128; ++i)
    {
        allValid &= isSlotActive(thisPtr, slotBase);
        slotBase += 0xF8;
    }

    // Check first batch of 5 slots at offset 0xA0, stride 0x30
    slotBase = thisPtr + 0xA0;
    for (i = 0; i < 5; ++i)
    {
        allValid &= isSlotActive(thisPtr, slotBase);
        slotBase += 0x30;
    }

    // Check second batch of 5 slots at offset 0x1A4, stride 0x30
    slotBase = thisPtr + 0x1A4;
    for (i = 0; i < 5; ++i)
    {
        allValid &= isSlotActive(thisPtr, slotBase);
        slotBase += 0x30;
    }

    // Check third batch of 5 slots at offset 0x2A8, stride 0x30
    slotBase = thisPtr + 0x2A8;
    for (i = 0; i < 5; ++i)
    {
        allValid &= isSlotActive(thisPtr, slotBase);
        slotBase += 0x30;
    }

    // Check individual slots at specific offsets
    allValid &= isSlotActive(thisPtr, thisPtr + 0x428);
    allValid &= isSlotActive(thisPtr, thisPtr + 0x398);
    allValid &= isSlotActive(thisPtr, thisPtr + 0x3C8);
    allValid &= isSlotActive(thisPtr, thisPtr + 0x3F8);

    return allValid;
}