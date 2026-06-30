// FUNC_NAME: SlotManager::resetAllSlots
void __fastcall SlotManager::resetAllSlots(int thisPtr)
{
    int* slotIter;
    int slotIndex;
    
    slotIter = (int*)(thisPtr + 0x24); // start of slot array (32 slots, each 40 bytes)
    slotIndex = 0x20; // 32 slots
    do {
        *(slotIter - 1) = 0; // clear field at offset -4 (maybe last field of previous slot, or a separate field before first slot)
        if (*slotIter != 0) {
            FUN_004daf90(slotIter); // likely delete/destroy the object pointed to
            *slotIter = 0;
        }
        // zero all other fields in the slot (offsets relative to slot start)
        slotIter[7] = 0; // +0x1C
        slotIter[8] = 0; // +0x20
        slotIter[5] = 0; // +0x14
        slotIter[2] = 0; // +0x08
        slotIter[3] = 0; // +0x0C
        slotIter[4] = 0; // +0x10
        slotIter += 10; // move to next slot (40 bytes = 10 ints)
        slotIndex--;
    } while (slotIndex != 0);
    
    // clear extra fields after the slot array
    slotIter = (int*)(thisPtr + 0x524);
    *(int*)(thisPtr + 0x520) = 0; // some count or pointer at +0x520
    if (*slotIter != 0) {
        FUN_004daf90(slotIter);
        *slotIter = 0;
    }
    *(int*)(thisPtr + 0x530) = 0; // +0x530
    *(int*)(thisPtr + 0x52c) = 0; // +0x52c
    *(int*)(thisPtr + 0x534) = 0; // +0x534
    return;
}