// FUNC_NAME: ReadStream::readAndDispatchCommand

void ReadStream::readAndDispatchCommand(void* handler) {
    // Offset 0x18 holds a pointer to the current read position
    uint32** readPtrPtr = (uint32**)((uint8*)this + 0x18);
    uint32* readPtr = *readPtrPtr;
    
    // Read command ID from the current (possibly misaligned) position
    uint32 commandId = *readPtr;
    
    // Align the pointer to the next 4-byte boundary (round up)
    uint32 alignedAddr = ((uint32)readPtr + 7) & 0xFFFFFFFC;
    uint8* alignedPtr = (uint8*)alignedAddr;
    *readPtrPtr = (uint32*)alignedPtr;
    
    // Copy 36-byte command data block from aligned position
    uint8 commandData[36];
    memcpy(commandData, alignedPtr, 36);
    
    // Advance read pointer past the command data
    *readPtrPtr = (uint32*)(alignedPtr + 36);
    
    // Read an 8-byte trailer after the command data
    uint64 trailer = *(uint64*)(alignedPtr + 36);
    uint32 trailerLow = (uint32)(trailer & 0xFFFFFFFF);
    uint32 trailerHigh = (uint32)(trailer >> 32);
    
    // Advance read pointer past the trailer
    *readPtrPtr = (uint32*)(alignedPtr + 44);
    
    // Extract the individual fields from the command data block
    uint64 data0 = *(uint64*)(commandData);          // first 8 bytes
    uint64 data1 = *(uint64*)(commandData + 8);      // next 8 bytes
    uint64 data2 = *(uint64*)(commandData + 16);     // next 8 bytes
    uint64 data3 = *(uint64*)(commandData + 24);     // next 8 bytes
    uint32 data4 = *(uint32*)(commandData + 32);     // last 4 bytes of 36-byte block
    
    // Call the handler function
    // handler is a pointer to a function pointer (double indirection)
    void (*handlerFunc)(uint32, uint64, uint64, uint64, uint64, uint32, uint32, uint32) = *(void (**)())(handler);
    handlerFunc(commandId, data0, data1, data2, data3, data4, trailerLow, trailerHigh);
}