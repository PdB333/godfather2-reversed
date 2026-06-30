// FUN_004563c0: GhostManager::addPendingGhostUpdate
uint32 GhostManager::addPendingGhostUpdate(uint32* pBufferHeader, int* pCount, int* pCapacity, uint32* pBuffer)
{
    // Copy current ghost pointer into "last added" slot
    *(uint32*)(this + 0x1C) = *(uint32*)(this + 0x14);
    
    uint32 uGhostId;
    if (*(uint32*)(this + 0x14) == 0)
    {
        uGhostId = 0;
    }
    else
    {
        uGhostId = generateGhostId(); // FUN_004cbd10
    }
    
    // Check if the dynamic array needs to grow
    int iCapacity = *pCapacity;
    if (*pCount == iCapacity)
    {
        int iNewCapacity;
        if (iCapacity == 0)
            iNewCapacity = 1;
        else
            iNewCapacity = iCapacity * 2;
        resizeGhostUpdateList(iNewCapacity); // FUN_00456a80 – assumes global list context
    }
    
    // Calculate new element offset (element size = 0x24)
    int iIndex = *pCount;
    uint8* pElement = (uint8*)(*pBuffer) + iIndex * 0x24;
    
    // Clear byte at offset +4 (likely a flag field)
    *(uint8*)(pElement + 4) = 0;
    
    // Increment count
    (*pCount) = iIndex + 1;
    
    // Store the ghost ID at the beginning of the new element
    *(uint32*)(*pBuffer + iIndex * 0x24) = uGhostId;
    
    return uGhostId;
}