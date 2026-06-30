// FUNC_NAME: BitStream::beginLocalBuffer
void BitStream::beginLocalBuffer()
{
    // Get the underlying buffer descriptor (this+0x1c points to a BufferDesc)
    BufferDesc* desc = *(BufferDesc**)(this + 0x1c);
    
    // Local buffer structure (stack-allocated temporary write area)
    struct {
        void* savedWritePtr; // offset 0: saved pointer (desc->writePtr +0x14)
        int    marker;       // offset 4: sentinel 0xFFFFFFFF
        int    sizeLimit;    // offset 8: from desc+0x34 (max bytes?)
        int    zero1;        // offset 12: always 0
        int    zero2;        // offset 16: always 0
    } localBuf;
    
    localBuf.savedWritePtr = *(void**)(desc + 0x14); // save current write pointer
    localBuf.marker        = -1;
    localBuf.sizeLimit     = *(int*)(desc + 0x34);  // save current size limit
    localBuf.zero1         = 0;
    localBuf.zero2         = 0;
    
    // Redirect descriptor's write pointer to the local buffer
    *(void**)(desc + 0x14) = &localBuf.savedWritePtr;
    
    // Write operations (e.g., header, data) now use the local stack buffer
    writeHeader(); // calls FUN_006417c0
    writeData();   // calls FUN_0063e400
}