// FUNC_NAME: SlotManager::addEntry
// Address: 0x00625340
// Description: Finds a free slot (flag == 0) in a 32-entry array and stores three associated integer values.

struct SlotManager {
    int count;           // +0x00
    int array1[32];      // +0x04
    int array2[32];      // +0x84
    int array3[32];      // +0x104
    char flags[32];      // +0x184
};

void __thiscall SlotManager::addEntry(int value1, int value2, int value3) {
    uint slot = 0;
    while (slot < 32) {
        if (flags[slot] == '\0')
            break;
        slot++;
    }
    if (slot >= 32)
        return; // no free slot

    flags[slot] = 1;           // mark slot as used
    array1[slot] = value1;     // +0x04 + slot*4
    array2[slot] = value2;     // +0x84 + slot*4
    array3[slot] = value3;     // +0x104 + slot*4
    count++;                   // +0x00
}