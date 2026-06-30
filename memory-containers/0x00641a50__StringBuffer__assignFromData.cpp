// FUNC_NAME: StringBuffer::assignFromData
// Address: 0x00641a50
// Reconstructed method for EARS::StringBuffer (or similar) that assigns data from a source string,
// reallocating internal buffer if necessary.

__thiscall uint __fastcall StringBuffer::assignFromData()
{
    // Get required size from source string (returns 0 if empty)
    uint requiredSize = getSourceLength();                       // FUN_00641940
    if (requiredSize == 0) {
        return 0;
    }

    // Buffer manager structure at this+0x08
    BufferManager* bufferMgr = reinterpret_cast<BufferManager*>(this->bufferManager);  // this+0x08

    // Reallocate if current capacity is insufficient
    if (bufferMgr->capacity < requiredSize) {
        if (requiredSize < 0x20) {
            requiredSize = 0x20;  // Minimum allocation size
        }
        char* newBuffer = reallocateBuffer(bufferMgr->capacity, requiredSize);  // FUN_006279a0
        bufferMgr->buffer = newBuffer;
        bufferMgr->capacity = requiredSize;
    }

    char* buffer = bufferMgr->buffer;                           // bufferMgr+0x00
    if (checkBuffer(buffer, requiredSize) != 0) {               // FUN_006385a0
        return handleBufferError();                             // FUN_00641890
    }

    // Copy source data (without trailing null) into buffer
    result = copyToBuffer(this->sourceData, buffer, requiredSize - 1);  // FUN_00638920
    return result;
}