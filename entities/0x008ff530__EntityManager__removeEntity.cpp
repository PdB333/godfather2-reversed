// FUNC_NAME: EntityManager::removeEntity
void __thiscall EntityManager::removeEntity(int param_1, int param_2)
{
    uint index;
    int currentPtr;
    int* localArray;

    index = 0;
    // Check if the entity ID array has entries
    if (*(uint*)(param_1 + 0x14) != 0) {
        localArray = *(int**)(param_1 + 0x10);
        do {
            if (*localArray == param_2) {
                // Found matching entity ID; remove it by calling the removal function with index
                if (index != 0xffffffff) {
                    FUN_008fef20(index);  // Likely removes the element and shifts the array
                }
                break;
            }
            index = index + 1;
            localArray = localArray + 1;
        } while (index < *(uint*)(param_1 + 0x14));
    }

    // Check if the entity ID matches the current selection (pointer offset 0x1c)
    if (*(int*)(param_1 + 0x1c) == 0) {
        currentPtr = 0;
    }
    else {
        // Subtract 0x48 to get the base of the owning structure (e.g., from a component pointer)
        currentPtr = *(int*)(param_1 + 0x1c) - 0x48;
    }
    if (currentPtr == param_2) {
        FUN_008ff3f0(0);  // Reset current selection or notify removal
    }
    return;
}