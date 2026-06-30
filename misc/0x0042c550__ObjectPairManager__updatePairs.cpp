// FUNC_NAME: ObjectPairManager::updatePairs
void __thiscall ObjectPairManager::updatePairs(void) {
    // Global flag to enable processing (DAT_01205358)
    if (!g_updatePairsEnabled) {
        return;
    }

    // Process 4 pairs of objects: two arrays at offsets 0x04 and 0x28 each holding 4 pointers
    // Each pair consists of (firstArray[i], secondArray[i])
    for (int i = 0; i < 4; i++) {
        // +0x04: pointer to first object in the pair
        EARSObject* first = this->firstObjects[i];   // offset 0x04 + i*4
        // +0x28: pointer to second object in the pair
        EARSObject* second = this->secondObjects[i]; // offset 0x28 + i*4

        // Call virtual method at vtable index 2 (offset 0x08) on both objects
        first->vtable->method2(first);
        second->vtable->method2(second);
    }
}