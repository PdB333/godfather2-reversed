// FUNC_NAME: EntityDataManager::registerFieldOffsets
void EntityDataManager::registerFieldOffsets(void* pSecondaryData) {
    // Define an array of field offsets (0x50, 0x60, 0x70, 0x80, 0x90)
    uint32_t fieldOffsets[5] = {
        0x50, // +0x50 (likely a size or struct offset)
        0x60, // +0x60
        0x70, // +0x70
        0x80, // +0x80
        0x90  // +0x90
    };
    // Call internal registration function with this pointer, secondary data, offsets array, and count
    FUN_004eba90(this, pSecondaryData, fieldOffsets, 5);
}