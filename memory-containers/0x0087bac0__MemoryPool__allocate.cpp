// FUNC_NAME: MemoryPool::allocate
int* __thiscall MemoryPool::allocate(int* this, int** ppOut, int arg3, int arg4)
{
    int* pAllocated;
    int* pPrev;
    int localVar;
    int buffer[2];
    int* pThisCopy;
    int flag;
    // Local matrix data (likely a 4x4 transformation)
    float matrix[16];

    *ppOut = 0;
    buffer[1] = 0;

    // Virtual call: likely to retrieve some data (e.g., a transform) into buffer[1]
    (this->vtable[0x94])(&buffer[1], arg4);

    // Read a 16-float matrix from global data (e.g., camera matrix)
    int* pGlobalMatrix = FUN_00471610();
    matrix[0]  = pGlobalMatrix[0];
    matrix[1]  = pGlobalMatrix[1];
    matrix[2]  = pGlobalMatrix[2];
    matrix[3]  = 0.0f;
    matrix[4]  = pGlobalMatrix[4];
    matrix[5]  = pGlobalMatrix[5];
    matrix[6]  = pGlobalMatrix[6];
    matrix[7]  = 0.0f;
    matrix[8]  = pGlobalMatrix[8];
    matrix[9]  = pGlobalMatrix[9];
    matrix[10] = pGlobalMatrix[10];
    matrix[11] = 0.0f;
    matrix[12] = pGlobalMatrix[12];
    matrix[13] = pGlobalMatrix[13];
    matrix[14] = pGlobalMatrix[14];
    matrix[15] = _DAT_00d5780c; // global constant

    // Determine allocation type based on a flag (likely from data at buffer[1] offset)
    buffer[1] = 3;
    if ((flag & 1) == 0) {
        buffer[1] = 2;
    }

    // Extract another flag
    int secondaryFlag = flag >> 2;
    pThisCopy = this;

    // Virtual call: likely to get allocation size or pool index
    int poolIndex = (this->vtable[0x58])(0, &buffer[1]);

    // Call actual memory allocation function
    pPrev = (int*)FUN_004df270(buffer, arg3, &matrix, poolIndex);

    // If ppOut previously pointed to a node, update its back-link to null
    if (*ppOut != 0) {
        *(int*)(*ppOut + 8) = 0;
        *ppOut = 0;
    }

    // Update output pointer and link new node into the list
    pAllocated = *pPrev;
    *ppOut = pAllocated;
    if (pAllocated != 0) {
        *(int**)(pAllocated + 8) = ppOut; // store pointer to the holder
        *pPrev = 0;                       // clear the source
    }

    // If the internal buffer[0] was non-null, update its back-link to null
    if (buffer[0] != 0) {
        *(int*)(buffer[0] + 8) = 0;
    }

    return ppOut;
}