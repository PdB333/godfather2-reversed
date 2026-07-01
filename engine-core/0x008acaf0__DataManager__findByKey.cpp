// FUNC_NAME: DataManager::findByKey
uint32_t __thiscall DataManager::findByKey(uint32_t param_1, uint32_t key) {
    uint32_t nodePtr;
    uint32_t current;
    uint32_t result;
    int compareResult;

    nodePtr = *(uint32_t *)(param_1 + 0x60); // +0x60: m_pRoot
    if (nodePtr == 0) {
        return 0xFFFFFFFF;
    }
    if (*(int *)(nodePtr + 8) == 0) { // +0x08: m_bValid or m_pChild
        nodePtr = 0;
    }
    while (true) {
        if (nodePtr == 0) {
            return 0xFFFFFFFF;
        }
        // Get current node data (e.g., pointer to node structure)
        current = (*(uint32_t (*)())PTR_FUN_00d79c8c)(); // global function pointer
        // Lock/reference the node
        FUN_004bb600(current); // likely lockNode
        // Compare key with node's key
        compareResult = FUN_004d4690(key); // likely compareKey
        if (compareResult == 0) {
            break;
        }
        // Move to next node
        (*(void (*)())PTR_FUN_00d79c90)(); // global function pointer, likely advance
    }
    // Get the data from the found node
    result = *(uint32_t *)((*(uint32_t (*)())PTR_FUN_00d79c8c)()); // dereference returned pointer
    return result;
}