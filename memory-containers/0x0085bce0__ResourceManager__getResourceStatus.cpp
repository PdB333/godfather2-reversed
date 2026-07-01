// FUNC_NAME: ResourceManager::getResourceStatus
uint ResourceManager::getResourceStatus(ResourceID* resourceId) {
    uint statusFlags = 0;
    ResourceEntry* entry = nullptr;
    uint* dataPtr = nullptr;
    
    // Look up the resource entry by ID and a specific hash (0xee654334)
    bool found = findResourceEntry(resourceId->id, 0xee654334, &entry, &dataPtr);
    
    if (found) {
        uint data = 0;
        // Check if entry and data pointer are valid, and entry type is 2
        if ((dataPtr != nullptr) && (entry != nullptr) && (entry->type == 2)) {
            data = *dataPtr;
        }
        // Build result: low byte set to 1, high bytes from (data >> 8)
        statusFlags = ((data >> 8) << 8) | 1;
        // If bit 2 of data is set, return the combined flags
        if ((data & 4) != 0) {
            return statusFlags;
        }
    }
    // Otherwise return statusFlags with low byte cleared
    return statusFlags & 0xFFFFFF00;
}