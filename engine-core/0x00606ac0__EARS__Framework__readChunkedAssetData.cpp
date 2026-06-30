// FUNC_NAME: EARS::Framework::readChunkedAssetData
// Function at 0x00606ac0: Reads a compressed asset by processing chunks defined in a global table.
// param_1: destination buffer (nullptr to only count required size)
// param_2: index into chunk table (0x1000 max, each entry 0x38 bytes)
// param_3: maximum output buffer size (used only for tracking when buffer non-null)
// Returns: total bytes written to buffer, or -1 on error, or 0 if buffer is null.

extern unsigned char g_chunkTable[0x1000 * 0x38]; // global table at 0x011a0f29
extern int readNextChunk(void); // reads next chunk from current stream, returns bytes read or -1

int readChunkedAssetData(char* dstBuf, unsigned int tableIndex, int bufSize)
{
    // Validate index range
    if (tableIndex >= 0x1000)
        return -1;

    // Get number of chunks for this asset from the table
    unsigned char chunkCount = g_chunkTable[tableIndex * 0x38];
    if (chunkCount == 0)
        return 0; // no chunks, nothing to read

    int remaining = bufSize;          // tracks remaining space (only used when dstBuf != nullptr)
    int totalBytes = 0;              // total bytes written
    for (int i = 0; i < chunkCount; i++)
    {
        int chunkSize = readNextChunk();
        if (chunkSize == -1)
            return 0;                // error reading chunk

        if (dstBuf != nullptr)
        {
            // Copy chunk data into buffer; readNextChunk() is assumed to fill dstBuf directly
            dstBuf += chunkSize;
            remaining -= chunkSize;
            totalBytes += chunkSize;
        }
        // When dstBuf is null, we still iterate through chunks but do not write
        // (this allows counting the total size without consuming memory)
    }

    // Return total bytes written (or 0 if dstBuf was null)
    return (dstBuf != nullptr) ? totalBytes : 0;
}