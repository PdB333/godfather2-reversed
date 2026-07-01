//FUNC_NAME: ObjectManager::setActiveObjectByID
void __thiscall ObjectManager::setActiveObjectByID(int thisPtr, int objectID) {
    // thisPtr: pointer to ObjectManager instance
    // objectID: ID of the object to activate (may be a pointer offset by 0x48?)
    if (objectID == 0) {
        return;
    }
    int count = *(int *)(thisPtr + 0x60); // +0x60: number of entries in the table
    if (count == 0) {
        return;
    }
    int *table = *(int **)(thisPtr + 0x5c); // +0x5c: pointer to array of ObjectEntry pairs (each 8 bytes)
    uint index = 0;
    while (true) {
        int entryID;
        if (table[0] == 0) {
            entryID = 0;
        } else {
            entryID = table[0] - 0x48; // stored value is ID + 0x48? Or pointer to object with ID at offset 0x48?
        }
        if (objectID == entryID) {
            break;
        }
        index++;
        table += 2; // advance to next entry (each entry is two ints)
        if (index >= (uint)count) {
            return;
        }
    }
    // Found matching entry at index
    FUN_0093f760(); // likely clears previous active state
    *(uint *)(thisPtr + 0x74) = index; // +0x74: store active index
    *(int *)(thisPtr + 0x58) = 0; // +0x58: reset some flag
    int objectField = *(int *)(objectID + 0x164); // +0x164: some field on the object
    int context = FUN_00950b20(); // returns some manager/context
    FUN_00976ac0(objectField, context); // perform activation
}