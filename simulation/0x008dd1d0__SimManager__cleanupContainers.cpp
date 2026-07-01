// FUNC_NAME: SimManager::cleanupContainers
void __fastcall SimManager::cleanupContainers() {
    int* nodePtr;
    int* dataPtr;

    // Process first container at +0x194
    dataPtr = *(int**)(this + 0x194);
    if (dataPtr != nullptr && dataPtr != (int*)0x48) {
        if (dataPtr == (int*)0) {
            nodePtr = nullptr;
        } else {
            nodePtr = (int*)((char*)dataPtr - 0x48);  // Get node header
        }
        // Call virtual release at vtable+0x6c on the node
        (**(code**)(*nodePtr + 0x6c))();
    }

    // Clean up secondary pointer at +0x1bc
    int* secondary = *(int**)(this + 0x1bc);
    if (secondary != nullptr && *(secondary + 2) != 0) {
        FUN_009e7530((int)secondary);
    }

    // Process second container at +0x18c
    dataPtr = *(int**)(this + 0x18c);
    if (dataPtr != nullptr && dataPtr != (int*)0x48) {
        if (dataPtr == (int*)0) {
            nodePtr = nullptr;
        } else {
            nodePtr = (int*)((char*)dataPtr - 0x48);
        }
        (**(code**)(*nodePtr + 0x6c))();
    }
}