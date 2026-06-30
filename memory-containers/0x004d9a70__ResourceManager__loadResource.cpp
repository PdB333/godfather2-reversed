// FUNC_NAME: ResourceManager::loadResource
// Address: 0x004d9a70
// This function loads a resource by ID, sets four handle fields in the object, and returns success status.
// It uses a callback (local_c) for cleanup if a data block is allocated.

bool __thiscall ResourceManager::loadResource(void* thisPtr, uint32_t resourceId)
{
    uint8_t* dataPtr;       // local_18
    int successFlag;        // local_14 (set by callees)
    void (*cleanupFn)(void*); // local_c
    uint32_t handle;        // result from getResourceHandle
    uint8_t result = 0;     // uVar3

    // Step 1: Parse or load the resource
    parseResourceID(resourceId);      // FUN_004d3bc0
    // Step 2: Initialize the resource system
    initResource();                   // FUN_004d54c0
    // Step 3: Mark that we are loading (might set successFlag)
    setLoadingFlag(1);                 // FUN_004d5900(1)

    // After these calls, local_14 and local_18 and local_c are set.
    // If successFlag is nonzero, we got a valid data pointer.
    if (successFlag != 0)
    {
        dataPtr = (uint8_t*)(local_18);
        if (dataPtr == (uint8_t*)0x0)
        {
            dataPtr = (uint8_t*)&DAT_0120546e; // default data?
        }
        // Get a resource handle (likely a pointer or ID)
        handle = getResourceHandle(dataPtr); // FUN_004dafd0
        // Copy the handle into four fields of this object
        *(uint32_t*)(thisPtr + 0x0) = handle;
        *(uint32_t*)(thisPtr + 0x4) = handle;
        *(uint32_t*)(thisPtr + 0x8) = handle;
        *(uint32_t*)(thisPtr + 0xC) = handle;
        result = 1; // success
    }

    // Cleanup: if we allocated a buffer, call the destructor callback
    if (local_18 != (uint8_t*)0x0)
    {
        (*cleanupFn)(local_18);
    }

    return result;
}