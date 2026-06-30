// FUNC_NAME: InputManager::resolveControllerMapping
bool __thiscall InputManager::resolveControllerMapping(int inputIndex, int* outMapping)
{
    // this+0x74: currentControllerSlot (short) - active controller slot number
    // this+0x70: pointer to mapping table structure (TableHeader)
    int currentSlot = *(short*)(this + 0x74);
    int index0 = (currentSlot < 0) ? -1 : currentSlot;

    // Structure at *(this+0x70):
    //   +0x18: number of slots in outer table
    //   +0x1c: pointer to outer table (array of OuterEntry, each 0x18 bytes)
    // OuterEntry: +0x8 = maxIndex (count), +0xc = pointer to inner table (array of ints, each 0x10 bytes)
    if (currentSlot >= 0) {
        int* tablePtr = *(int**)(this + 0x70);
        int slotCount = *(int*)(tablePtr + 0x18);
        if (slotCount > currentSlot && inputIndex >= 0) {
            char* outerEntries = (char*)*(int*)(tablePtr + 0x1c);
            int entryMaxIndex = *(int*)(outerEntries + 8 + currentSlot * 0x18);
            if (entryMaxIndex > inputIndex) {
                int* innerTable = *(int**)(outerEntries + 0xc + currentSlot * 0x18);
                index0 = *(int*)((char*)innerTable + inputIndex * 0x10);
            } else {
                index0 = -1;
            }
        } else {
            index0 = -1;
        }
    }
    outMapping[0] = index0;

    // Second lookup: use index0 to get index1
    int index1 = (currentSlot < 0) ? -1 : currentSlot;
    if (currentSlot >= 0) {
        int* tablePtr = *(int**)(this + 0x70);
        int slotCount = *(int*)(tablePtr + 0x18);
        if (slotCount > currentSlot && index0 >= 0) {
            char* outerEntries = (char*)*(int*)(tablePtr + 0x1c);
            int entryMaxIndex = *(int*)(outerEntries + 8 + currentSlot * 0x18);
            if (entryMaxIndex > index0) {
                int* innerTable = *(int**)(outerEntries + 0xc + currentSlot * 0x18);
                index1 = *(int*)((char*)innerTable + index0 * 0x10);
            } else {
                index1 = -1;
            }
        } else {
            index1 = -1;
        }
    }
    outMapping[1] = index1;

    // Third lookup: use index1 to get index2
    int index2 = (currentSlot < 0) ? -1 : currentSlot;
    if (currentSlot >= 0) {
        int* tablePtr = *(int**)(this + 0x70);
        int slotCount = *(int*)(tablePtr + 0x18);
        if (slotCount > currentSlot && index1 >= 0) {
            char* outerEntries = (char*)*(int*)(tablePtr + 0x1c);
            int entryMaxIndex = *(int*)(outerEntries + 8 + currentSlot * 0x18);
            if (entryMaxIndex > index1) {
                int* innerTable = *(int**)(outerEntries + 0xc + currentSlot * 0x18);
                index2 = *(int*)((char*)innerTable + index1 * 0x10);
            } else {
                index2 = -1;
            }
        } else {
            index2 = -1;
        }
    }
    outMapping[2] = index2;

    // Fourth lookup: use index2 to get index3
    int index3 = -1;
    if (currentSlot >= 0) {
        int* tablePtr = *(int**)(this + 0x70);
        int slotCount = *(int*)(tablePtr + 0x18);
        if (slotCount > currentSlot && index2 >= 0) {
            char* outerEntries = (char*)*(int*)(tablePtr + 0x1c);
            int entryMaxIndex = *(int*)(outerEntries + 8 + currentSlot * 0x18);
            if (entryMaxIndex > index2) {
                int* innerTable = *(int**)(outerEntries + 0xc + currentSlot * 0x18);
                index3 = *(int*)((char*)innerTable + index2 * 0x10);
            } else {
                index3 = -1;
            }
        } else {
            index3 = -1;
        }
    }
    outMapping[3] = index3;

    // Validate that all indices are valid and the chain passes multiple checks
    if (inputIndex >= 0 && index0 >= 0 && index1 >= 0 && index2 >= 0 && index3 >= 0) {
        // FUN_0058dd70 is probably a validation function for each mapping step
        if (FUN_0058dd70() && FUN_0058dd70() && FUN_0058dd70() && FUN_0058dd70() && FUN_0058dd70()) {
            return true;
        }
    }
    return false;
}