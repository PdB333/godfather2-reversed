// FUNC_NAME: EntityGroupManager::markGroupEntitiesForUpdate
void __thiscall EntityGroupManager::markGroupEntitiesForUpdate(int this)
{
    // Check if bit 4 in flags is already set; if so, skip
    uint flags = *(uint *)(this + 0x34);
    if ((flags >> 4 & 1) != 0) {
        return;
    }

    // Set bit 4 to indicate we are processing
    *(uint *)(this + 0x34) = flags | 0x10;

    // Check if manager (pointed by +0x10) has its +0xd4 field == 0 (e.g., not busy)
    int* manager = *(int **)(this + 0x10);
    if (manager == 0 || *(int *)(manager + 0xd4) != 0) {
        return;
    }

    uint count = *(uint *)(this + 0x20);
    if (count == 0) {
        return;
    }

    // Iterate over children list, starting at +0x1c (array of pointers)
    uint index = 0;
    do {
        int childEntity = *(int *)(*(int *)(this + 0x1c) + index * 4);
        char conditionMet = FUN_00791230();  // random/conditional check
        if (conditionMet != 0) {
            uint childFlags = *(uint *)(childEntity + 0x5c);
            // If bit 20 (0x100000) is not set, mark for update by setting bit 23 (0x800000)
            if ((childFlags >> 0x14 & 1) == 0) {
                *(uint *)(childEntity + 0x5c) = childFlags | 0x800000;
            }
        }
        index++;
    } while (index < count);
}