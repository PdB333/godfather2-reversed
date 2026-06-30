// FUNC_NAME: SlotPool::getSlot
int SlotPool::getSlot(int key) {
    int index = findIndex(key);  // FUN_004830a0: returns slot index or -1
    if (index >= 0) {
        int* arrayBase = *(int**)(this + 0x1c);  // +0x1c: pointer to slot array
        int* slotEntry = arrayBase + 4 + index * 8;  // each slot entry: offset 4, stride 8
        if (slotEntry != nullptr && *slotEntry != 0) {
            return *slotEntry;  // existing valid slot
        }
    }
    // No valid slot found – allocate new
    void* mem = alloc(0x214);  // FUN_009c8e50: allocate 532 bytes
    if (mem != nullptr) {
        int newSlot = constructSlot(key);  // FUN_004826f0: initialize slot
        setSlotPointer(key, newSlot);      // FUN_00482e10: store slot pointer
        return newSlot;
    }
    setSlotPointer(key, 0);
    return 0;
}