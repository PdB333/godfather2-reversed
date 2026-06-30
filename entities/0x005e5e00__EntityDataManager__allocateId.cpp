// FUNC_NAME: EntityDataManager::allocateId
uint32_t EntityDataManager::allocateId() {
    // Offset 0x6038: Counter for generating unique, non-zero IDs
    uint32_t *idCounter = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x6038);
    *idCounter = *idCounter + 1;
    // Ensure ID is never zero (zero is reserved as invalid/null)
    if (*idCounter == 0) {
        *idCounter = 1;
    }
    return *idCounter;
}