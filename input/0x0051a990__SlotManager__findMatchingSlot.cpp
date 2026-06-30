// FUNC_NAME: SlotManager::findMatchingSlot
int __thiscall SlotManager::findMatchingSlot(void* this, void* param2) {
    int count = *(unsigned char*)((int)this + 0x1c); // +0x1c: number of slots (byte)
    if (count == 0) {
        return -1;
    }

    int* slotArray = (int*)((int)this + 0x30); // +0x30: start of slot array (each slot 0x24 bytes)
    for (int i = 0; i < count; ++i) {
        int* slotObject = (int*)*slotArray; // slot[0]: pointer to the object
        if (slotObject != nullptr) {
            // vtable offset 0x30: object->isMatch(param2, slot+12)
            // Each slot: +0 = object pointer, +12 = data block (3 ints)
            typedef bool (__thiscall* MatchFunc)(void*, void*);
            MatchFunc matchFunc = (MatchFunc)(*(int*)slotObject + 0x30);
            if (matchFunc(slotObject, slotArray + 3)) {
                return i;
            }
        }
        slotArray += 9; // next slot (9 ints = 36 bytes)
    }
    return -1;
}