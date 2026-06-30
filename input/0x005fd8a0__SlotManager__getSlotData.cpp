// FUNC_NAME: SlotManager::getSlotData
// Function address: 0x005fd8a0
// Role: Retrieves a value associated with a slot index from two parallel arrays.
// The first array at +0x70 contains flags (nonzero means valid), second at +0x78 contains data.
// If the flag for the given index is non-zero, the data is copied to the output pointer.

void __thiscall SlotManager::getSlotData(int *slotIndex, int *outData)
{
    int flag = *(int*)(this + 0x70 + *slotIndex * 0xC); // +0x70: flag array, 12 bytes per slot
    int data = 0;
    if (flag != 0) {
        data = *(int*)(this + *slotIndex * 0xC + 0x78); // +0x78: data array, same indexing structure
    }
    if (data != 0) {
        *outData = data;
    }
}