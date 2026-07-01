// FUNC_NAME: UnknownClass::findValueByKey
int __thiscall UnknownClass::findValueByKey(int this, int key) {
    uint slotCount = *(uint *)(this + 0x134); // number of slots
    int foundValue = 0;

    if (slotCount == 0) {
        return 0;
    }

    int *slotPtr = *(int **)(this + 0x130); // pointer to slot array (each slot 0x1c bytes)
    for (uint slotIdx = 0; slotIdx < slotCount; slotIdx++) {
        uint keyCount = *(uint *)(slotPtr + 0x14); // +0x14: number of keys in this slot
        if (keyCount != 0) {
            int *keyArray = *(int **)(slotPtr + 0x10); // +0x10: pointer to key array
            for (uint keyIdx = 0; keyIdx < keyCount; keyIdx++) {
                if (key == keyArray[keyIdx]) {
                    int slotValue = *(int *)(slotPtr + 0x4); // +0x04: associated value
                    if (slotValue != 0) {
                        return slotValue; // found non-zero value
                    }
                    // zero value is considered "not found", continue searching
                    break;
                }
            }
        }
        slotPtr += 0x1c / sizeof(int); // advance to next slot (0x1c bytes = 7 ints)
    }
    // If we reach here, either no match or match had value zero
    return foundValue; // always 0 at this point
}