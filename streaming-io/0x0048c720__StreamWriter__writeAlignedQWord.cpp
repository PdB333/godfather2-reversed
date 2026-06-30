// FUNC_NAME: StreamWriter::writeAlignedQWord
void __thiscall StreamWriter::writeAlignedQWord(int* this, undefined4 low, undefined4 high) 
{
    // Dereference 'this' to get the actual internal buffer pointer
    int* bufferPtr = *this; // bufferPtr points to the stream's data area
    
    // Set up vtable pointer at offset 0x14 (5th word) to a known function pointer table
    **(undefined4**)(bufferPtr + 0x14) = &PTR_FUN_01123d64;
    
    // Advance the write position by 4 bytes (skip the vtable pointer)
    int* writePosPtr = (int*)(bufferPtr + 0x14);
    *writePosPtr = *writePosPtr + 4;
    
    // Re-fetch the buffer pointer (might have been invalidated)
    bufferPtr = *this;
    
    // Align current write position to 8-byte boundary
    undefined8* alignedWritePos = (undefined8*)(*(int*)(bufferPtr + 0x14) + 3U & 0xfffffffc);
    *(undefined8**)(bufferPtr + 0x14) = alignedWritePos;
    
    // Write the 64-bit value formed by low and high parameters
    *alignedWritePos = CONCAT44(high, low);
    
    // Advance write position by 8 bytes (size of QWord)
    *(int*)(bufferPtr + 0x14) = *(int*)(bufferPtr + 0x14) + 8;
    
    // Write a 4-byte value from uninitialized register (likely a bug; original may have had a 3rd parameter)
    // In practice, unaff_ESI should be replaced by a meaningful value, e.g., a third function parameter.
    // For reconstruction, we assume a third parameter named 'extra'.
    undefined4 extra = UNUSED; // place for the missing parameter
    **(undefined4**)(bufferPtr + 0x14) = extra;
    
    // Finalize the write position
    *(int*)(bufferPtr + 0x14) = *(int*)(bufferPtr + 0x14) + 4;
    
    return;
}