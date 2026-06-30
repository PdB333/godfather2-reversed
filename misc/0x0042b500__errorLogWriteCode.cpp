// FUNC_NAME: errorLogWriteCode
// Address: 0x0042b500
// Writes an error code (short) into a per-thread slot at index param_1, 
// and if thread's logging flag is not 1, also appends the pair (param_1, param_2) into a global error log buffer.
// The global buffer is allocated from a bump allocator at gErrorLogAllocator + 0x14.
// The buffer is prefixed with a static vtable pointer (PTR_LAB_0110b824), likely for a log entry structure.

void errorLogWriteCode(int errorIndex, short errorData)
{
    // Thread-specific data pointer from FS segment (TLS)
    // FS:[0x2C] -> TEB field ???, then +0x34 gives a pointer to a per-thread structure
    int* threadData = *(int**)(__readfsdword(0x2C));
    int logFlag = *(int*)(threadData + 0x34); // +0x34: flag controlling global logging (1 = suppress)
    
    // Write error data into per-thread slot array at offset 0x10 + index * 2
    short* slotArray = (short*)(threadData + 0x10);
    slotArray[errorIndex] = errorData;
    
    if (logFlag != 1)
    {
        // Global bump allocator for error log entries
        uint** allocatorPtr = (uint**)(gErrorLogAllocator + 0x14); // +0x14: pointer to current allocation position
        // Initialize the first 4 bytes of the new allocation with a static vtable pointer
        **(uint***)allocatorPtr = &PTR_LAB_0110b824;
        (*allocatorPtr)++; // advance past the vtable pointer (4 bytes)
        
        // Align to 4-byte boundary (already aligned after increment)
        int* alignedPos = (int*)(*allocatorPtr);
        *alignedPos = errorIndex; // write the error index (4 bytes)
        (*allocatorPtr)++; // advance 4 bytes
        
        // Write the error data (2 bytes) and advance with alignment to 4 bytes, +5 & 0xfffffffc effectively rounds up to next 4-byte boundary
        short* dataPos = (short*)(*allocatorPtr);
        *dataPos = errorData;
        uint newPos = (uint)(dataPos + 1); // advance 2 bytes
        *allocatorPtr = (newPos + 3) & 0xfffffffc; // align to 4 bytes
    }
}