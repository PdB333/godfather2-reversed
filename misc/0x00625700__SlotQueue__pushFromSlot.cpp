// FUNC_NAME: SlotQueue::pushFromSlot
void __fastcall SlotQueue::pushFromSlot(int thisPtr, int slotIndex)
{
    // +0x08: int* writePtr (current position in ring buffer)
    // +0x0C: int* slotBase (pointer to start of 8-byte slot array, 1-indexed)
    int* writePtr = *(int**)(thisPtr + 8);
    int* src;
    if (slotIndex > 0)
    {
        // slotIndex is 1-based; compute source address: slotBase + (slotIndex-1)*8
        src = (int*)(*(int*)(thisPtr + 0xC) - 8 + slotIndex * 8);
    }
    else
    {
        // Use a default/empty slot returned by helper function
        src = (int*)FUN_00625430();
    }
    // Copy 8 bytes (two ints) from source to current write position
    writePtr[0] = src[0];
    writePtr[1] = src[1];
    // Advance write pointer by 8 bytes
    *(int*)(thisPtr + 8) = (int)writePtr + 8;
}