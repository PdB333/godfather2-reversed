// FUNC_NAME: findPackedSlot
int __thiscall findPackedSlot(int key) {
    int zeroCount = 0;
    int valueFromSlot = 0; // value from the last slot (top 24 bits of slot, shifted 8 bits)

    int* slots = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x34);

    for (int i = 0; i < 4; ++i) {
        int slot = slots[i];
        valueFromSlot = slot >> 8;

        if (key == slot) {
            // found matching slot: return its value with flag bit 1 set
            return (valueFromSlot << 8) | 1;
        }
        if (slot == 0) {
            ++zeroCount;
        }
    }

    // If we reach here, no match found
    if (key != 0 && zeroCount != 4) {
        // There are non-zero slots, so return the last slot's value without flag
        return valueFromSlot << 8;
    } else {
        // Either key is 0 (special case) or all slots are empty -> return last value with flag 1
        return (valueFromSlot << 8) | 1;
    }
}