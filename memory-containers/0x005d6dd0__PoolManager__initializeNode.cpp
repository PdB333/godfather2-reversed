// FUNC_NAME: PoolManager::initializeNode

void __cdecl PoolManager::initializeNode(void)
{
    // Get the address of the buffer pointer stored at global address (DAT_01206880 + 0x14)
    int* ppBuffer = (int*)(DAT_01206880 + 0x14);

    // Set the vtable pointer for the new node
    *(void**)(*ppBuffer) = &PTR_LAB_01126e88;

    // Advance the buffer pointer past the vtable (4 bytes)
    *ppBuffer = (int)((char*)*ppBuffer + 4);

    // Now point to the data portion of the node
    int* pData = (int*)*ppBuffer;

    // Initialize the first 4 fields to zero
    pData[0] = 0; // likely pointer or flag
    pData[1] = 0; // +0x04
    pData[2] = 0; // +0x08
    pData[3] = 0; // +0x0C

    // Set the fifth field to a global constant (address or value)
    pData[4] = DAT_00e2b1a4; // +0x10

    // Advance the buffer pointer past these 5 fields (20 bytes)
    *ppBuffer = (int)(pData + 5);

    // Write a flag value (0x3f) at the new offset (offset 0x18 from node start)
    pData[5] = 0x3f; // +0x14

    // Advance buffer pointer past this last field (4 bytes)
    *ppBuffer = (int)((int)*ppBuffer + 4);
}