//FUNC_NAME: EntityManager::processRegisteredComponents
void __thiscall EntityManager::processRegisteredComponents(void) {
    // Check if processing is already in progress (bit 25 of flags at +0x5c) and if component list exists (+0xac)
    if (((*(uint *)(this + 0x5c) >> 0x19 & 1) == 0) && (*(int *)(this + 0xac) != 0)) {
        // Set processing flag (bit 25)
        *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) | 0x2000000;

        // Get component list structure: pointer at +0xac points to { int** array; int count; }
        int componentListPtr = *(int *)(this + 0xac);
        int count = *(int *)(componentListPtr + 4);          // +0x04: number of components
        int** componentArray = *(int ***)componentListPtr;   // +0x00: pointer to array of component pointers

        // Iterate in reverse order
        for (int i = count - 1; i >= 0; i--) {
            int* component = componentArray[i];
            if (component != nullptr) {
                // Call virtual function at vtable+4 (e.g., update, notify)
                (**(code **)(*component + 4))(this);
            }
        }

        // Post-processing / finalization
        FUN_007909d0();
    }
}