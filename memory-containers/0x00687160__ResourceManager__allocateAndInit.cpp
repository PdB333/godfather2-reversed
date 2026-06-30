// FUNC_NAME: ResourceManager::allocateAndInit
void* ResourceManager::allocateAndInit(int param_2) {
    struct AllocationParams {
        int mode;
        int size;
        int flags;
    };

    AllocationParams params;
    params.mode = 2;       // e.g., MODE_RESOURCE_BUFFER
    params.size = 0x10;    // alignment or sub-size
    params.flags = 0;      // reserved

    int result = this->allocateMemory(10000, &params, param_2);
    if (result != 0) {
        return this->initializeObject(this);
    }
    return 0;
}