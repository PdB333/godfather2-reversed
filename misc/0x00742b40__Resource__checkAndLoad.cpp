// FUNC_NAME: Resource::checkAndLoad
uint32_t __fastcall Resource::checkAndLoad(Resource* pThis) {
    // pThis is a pointer to the Resource object
    uint32_t state = *(uint32_t*)((uint8_t*)pThis + 0x54); // m_pResourceData -> pointer to subobject
    // Check if state is null or if the subobject is at a specific offset (0x48)
    if ((state == 0) || ((state - 0x48) == 0)) {
        return state & 0xFFFFFF00; // Return error code (clear low byte)
    }

    uint32_t localVar8 = 0;
    uint32_t localVar4 = 0; // unused

    // Get the vtable base: the parent object of the subobject is at offset -0x48
    ResourceDataBase* resourceData = nullptr;
    if (state == 0) {
        resourceData = nullptr;
    } else {
        resourceData = (ResourceDataBase*)(state - 0x48);
    }

    // iVar1 = pThis->m_completionCallback (offset 0x5c)
    void* completionCallback = (void*)((uint8_t*)pThis + 0x5c);

    // Call virtual function at vtable index 0x1ec (setupCompletion)
    resourceData->vtable[0x1ec / 4](completionCallback, &localVar8);

    // Call engine functions to validate the resource and completion
    uint32_t validationResult = FUN_00542f80(*(uint32_t*)((uint8_t*)pThis + 0x50), completionCallback);
    if ((char)validationResult != 0) {
        validationResult = FUN_00878e30(*(uint32_t*)((uint8_t*)pThis + 0x50), completionCallback);
        if ((char)validationResult != 0) {
            // Recompute resourceData pointer (redundant in this path)
            if (state == 0) {
                resourceData = nullptr;
            } else {
                resourceData = (ResourceDataBase*)(state - 0x48);
            }
            // Call virtual function at vtable index 500 (0x1F4) - processResult
            uint32_t result = resourceData->vtable[500 / 4](/* argument unknown: likely completionCallback */);
            if (result == 0) {
                return 1; // Success
            }
        }
    }
    return state & 0xFFFFFF00; // Return error code with low byte cleared
}