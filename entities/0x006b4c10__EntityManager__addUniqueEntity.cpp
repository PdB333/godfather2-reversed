// FUNC_NAME: EntityManager::addUniqueEntity
void __thiscall EntityManager::addUniqueEntity(int param_1, int param_2) {
    uint index;
    int *elementPtr;
    int *globalManager;

    // Search for existing element
    index = 0;
    if (*(uint *)(param_1 + 0xb8) != 0) {
        elementPtr = *(int **)(param_1 + 0xb4);
        do {
            if (*elementPtr == param_2) {
                if (-1 < (int)index) {
                    return; // Already present, no duplicate
                }
                break;
            }
            index++;
            elementPtr++;
        } while (index < *(uint *)(param_1 + 0xb8));
    }

    // Register a global callback on first addition
    globalManager = FUN_00791300(); // Likely GameManager::getInstance()
    if ((globalManager != 0) && (*(int *)(globalManager + 0x158) == 0)) {
        *(undefined1 **)(globalManager + 0x158) = &LAB_006b2cc0; // Set callback to onFirstAdd
    }

    // Ensure capacity, double if needed
    int capacity = *(int *)(param_1 + 0xbc);
    int count = *(int *)(param_1 + 0xb8);
    if (count == capacity) {
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        FUN_006b1e10(newCapacity); // resizeArray()
    }

    // Append new element
    int *array = *(int **)(param_1 + 0xb4);
    array[*(int *)(param_1 + 0xb8)] = param_2;
    *(int *)(param_1 + 0xb8) = count + 1;

    // Notify listeners / update
    FUN_006b2f70(); // onArrayChanged()
    return;
}