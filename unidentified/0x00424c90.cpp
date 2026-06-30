// FUN_NAME: SlotManager::findSlotIndex
uint __thiscall SlotManager::findSlotIndex(uint *this, int value)
{
    int *currentSlot;
    uint index;
    
    // +0x154: count of slots (number of elements in the array at +0x158)
    // +0x158: array of slot values (int)
    if (this[0x154 / 4] != 0) { // this[0x55] as uint, but careful: offset 0x154 is in bytes, so (0x154/4)=0x55
        currentSlot = (int *)((char *)this + 0x158); // pointer to first slot
        index = 0;
        while (*currentSlot != value) {
            index++;
            currentSlot++;
            if ((uint)this[0x154 / 4] <= index) {
                return 4; // sentinel value: not found (max index 3 for 4-element array)
            }
        }
    }
    return index;
}