// FUNC_NAME: SlotContainer::collectUniqueIDs
// Address: 0x007dcf50
// Collects unique IDs from an array of 4-field slot structures and stores them in a result array (max 4).
// Offsets:
//   0x54: start of slot array (each slot is 16 bytes: int field1, int field2, int field3, int field4)
//   0x94: count of slots (uint)
//   0x98: result array (int[4])
//   0xa8: number of IDs in result array (uint, max 4)
int* __thiscall SlotContainer::collectUniqueIDs(int this) {
    uint slotCount = *(uint*)(this + 0x94);
    int* resultPtr = (int*)(this + 0x98);
    uint resultCount = *(uint*)(this + 0xa8);
    // slot array starts at this+0x54, each slot is 4 ints
    struct Slot { int field1; int field2; int field3; int field4; };
    Slot* slots = (Slot*)(this + 0x54);

    for (uint i = 0; i < slotCount; i++) {
        Slot* slot = &slots[i];
        int id = FUN_0088db10(slot->field1, slot->field2, slot->field3, slot->field4);
        if (id != 0) {
            // Check if ID already in result array
            bool alreadyPresent = false;
            for (uint j = 0; j < resultCount; j++) {
                if (resultPtr[j] == id) {
                    alreadyPresent = true;
                    break;
                }
            }
            if (!alreadyPresent && resultCount < 4) {
                resultPtr[resultCount] = id;
                resultCount++;
                *(uint*)(this + 0xa8) = resultCount; // update count in object
            }
        }
    }
    return resultPtr;
}