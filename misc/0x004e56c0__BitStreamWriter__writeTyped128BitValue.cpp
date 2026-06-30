// FUNC_NAME: BitStreamWriter::writeTyped128BitValue
// Address: 0x004e56c0
// Serializes a 16-byte value with a type tag into a buffer managed by this writer.
// The buffer state structure has a write pointer at offset +0x14.
void __thiscall BitStreamWriter::writeTyped128BitValue(int* thisPtr, int32_t typeId, const uint64_t* value128) {
    // Dereference thisPtr to get the buffer state object (e.g., a member pointer)
    int* bufferState = (int*)*thisPtr;
    
    // Write pointer is at offset +0x14 of bufferState
    int** writePtrLoc = (int**)(bufferState + 0x14); // +0x14: mWritePtr
    int* writePtr = *writePtrLoc;
    
    // Write a type marker (pointer to a static label)
    *(int**)writePtr = &PTR_LAB_01124acc; // type descriptor
    writePtr = writePtr + 1; // advance by 4 bytes (one int)
    
    // Write the type id
    *(int*)writePtr = typeId;
    
    // Align to 16-byte boundary (round up to next 0x10)
    // Equivalent to: writePtr = (int*)(((uint32_t)(writePtr + 1) + 0x13) & 0xFFFFFFF0)
    writePtr = (int*)(((uint32_t)(writePtr + 1) + 0x13) & 0xFFFFFFF0);
    
    // Write the 16-byte value (two 8-byte halves)
    *(uint64_t*)writePtr = value128[0];
    *(uint64_t*)(writePtr + 2) = value128[1]; // +2 ints = +8 bytes
    writePtr = writePtr + 4; // advance by 16 bytes (4 ints)
    
    // Store updated write pointer back
    *writePtrLoc = writePtr;
}