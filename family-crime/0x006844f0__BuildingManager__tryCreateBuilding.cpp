// FUNC_NAME: BuildingManager::tryCreateBuilding
int BuildingManager::tryCreateBuilding(int param_2) {
    AllocationInfo allocInfo;
    allocInfo.type = 2;
    allocInfo.size = 0x10;
    allocInfo.flags = 0;

    // Attempt to allocate internal resource (size 0x100, descriptors from allocInfo, context param_2)
    void* allocated = heapAllocate(0x100, &allocInfo, param_2);
    if (allocated != nullptr) {
        // Initialize the building object using the passed 'this' pointer
        return initializeBuilding(this);
    }
    return 0;
}