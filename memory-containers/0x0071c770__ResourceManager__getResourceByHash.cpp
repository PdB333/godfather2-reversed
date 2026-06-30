// FUNC_NAME: ResourceManager::getResourceByHash
// Address: 0x0071c770
// This function retrieves a specific resource (identified by hash 0x55859efa) from the resource cache.
// It uses a virtual method to look up the resource, then either returns the cached data or loads default data.
// The result is passed to a processing function (FUN_0071c440) with additional arguments.
void __thiscall ResourceManager::getResourceByHash(ResourceManager* this, int unkParam) {
    int* cachedHandle;  // local_20 - handle into cache list
    undefined8* cachedData; // local_18 - pointer to resource data
    undefined8 resourceData; // local_14 - output data structure (8 bytes)
    undefined4 extraData; // uStack_c - part of resourceData
    char found; // cVar1

    cachedHandle = 0;
    resourceData = 0;
    cachedData = 0;
    
    // Call virtual function at vtable offset +0x10 to look up the resource by hash
    // Returns non-zero if entry found, and fills cachedHandle with a handle/index
    found = (this->vtbl[4])(0x55859efa, &cachedHandle);  // +0x10 = +4 in pointer table
    
    if (found != 0) {
        // Get pointer to the current cache entry list (likely a linked list or array)
        int* listPtr = getCacheList();  // FUN_007ffdf0
        if (&cachedHandle != listPtr) {
            int currentHandle = *listPtr;
            if (cachedHandle != currentHandle) {
                // Release old cached handle if valid
                if (cachedHandle != 0) {
                    releaseHandle(&cachedHandle);  // FUN_004daf90
                }
                cachedHandle = currentHandle;
                if (currentHandle != 0) {
                    // Update the list pointer to point to the new handle
                    *(int**)(currentHandle + 4) = &cachedHandle;
                }
            }
        }
        // Retrieve the actual data pointer from the list entry (offset +0x8)
        cachedData = (undefined8*)listPtr[2];
    }
    
    if (cachedHandle == 0) {
        // No cached entry: get default data from global (likely a singleton)
        int globalPtr = getGlobalData();  // FUN_00471610
        resourceData = *(undefined8*)(globalPtr + 0x30);
        extraData = *(undefined4*)(globalPtr + 0x38);
    } else {
        // Use cached data: it's stored as an 8-byte value at cachedData
        extraData = *(undefined4*)(cachedData + 1);
        resourceData = *cachedData;
    }
    
    // Call the core processing function with the unkParam, this, a global constant, and the resource data
    processResource(unkParam, this, GLOBAL_RESOURCE_CTX, &resourceData);  // FUN_0071c440
    
    // Release the handle if it was used
    if (cachedHandle != 0) {
        releaseHandle(&cachedHandle);  // FUN_004daf90
    }
}