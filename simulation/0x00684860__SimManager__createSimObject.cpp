// FUNC_NAME: SimManager::createSimObject
uint SimManager::createSimObject(void* pManager, void* pCreationData)
{
    SimObjectCreationParams params;
    params.type = 2;               // +0x00: object type identifier
    params.size = 0x10;            // +0x04: object size or subtype
    params.flags = 0;              // +0x08: creation flags (unused)
    
    // Attempt to allocate a new SimObject of size 0x68 (104 bytes)
    void* pObject = allocateObject(0x68, &params, pCreationData);
    if (pObject != nullptr)
    {
        // Retrieve the result from the manager (e.g., interface pointer)
        return getObjectResult(pManager);
    }
    return 0;
}