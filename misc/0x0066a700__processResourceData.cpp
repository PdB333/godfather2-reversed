// FUNC_NAME: processResourceData
int processResourceData(void* pSource, void* pDest)
{
    int result;
    void* workspaceBuffer;
    struct {
        int offset;   // +0x00 (local_10)
        int size;     // +0x04 (local_c)
        int flags;    // +0x08 (local_8)
    } bufferInfo;

    // Allocate workspace (256 bytes = 4 * 0x40)
    workspaceBuffer = calloc(4, 0x40);
    if (workspaceBuffer == nullptr)
    {
        return -2;
    }

    bufferInfo.offset = 0;
    bufferInfo.size = 0x40;
    bufferInfo.flags = 0;

    // Initialize buffer info from source data
    result = initializeBufferInfo(pSource, &bufferInfo);
    if (result == 0)
    {
        // Process data using buffer info and destination
        result = processDataWithBuffer(&bufferInfo, pDest);
    }

    // Finalize / cleanup (likely global state)
    cleanup();

    return result;
}