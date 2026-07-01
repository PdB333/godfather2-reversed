// FUNC_NAME: EntityDataManager::removeEntityByID
void __thiscall EntityDataManager::removeEntityByID(int entityID) {
    uint count = *(uint *)(this + 0x148);       // +0x148: number of entries in the ID array
    uint i = 0;
    uint foundIndex = 0xFFFFFFFF;               // default: not found

    if (count != 0) {
        do {
            foundIndex = i;
            // +0x80: base of array of int IDs
            if (*(int *)(this + 0x80 + i * 4) == entityID) {
                break;                          // found matching ID
            }
            i++;
            if (i >= count) {                   // reached end without match
                removeEntityAtIndex(0xFFFFFFFF); // call removal function with -1 (not found)
                return;
            }
        } while (true);
    }

    removeEntityAtIndex(foundIndex);            // call removal function with the found index (or -1 if count==0)
}