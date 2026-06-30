// FUNC_NAME: PacketBuffer::writeFixedDataBlock
void __thiscall PacketBuffer::writeFixedDataBlock(int *thisPtr, int typeId, int64 data0, int64 data1, int64 data2, int64 data3, int extra32, int valueLow, int valueHigh)
{
    // thisPtr points to a PacketBuffer object.
    // At offset 0: a pointer to the underlying buffer.
    int *bufferBase = (int *)*thisPtr; // Get the buffer pointer from the object.
    
    // The buffer has a current write pointer stored at offset +0x14 from its start.
    // This pointer is initially set to point to the data area after a header.
    
    // Write a vtable pointer (constructor or type table) at the current write location.
    **(int **)(bufferBase + 0x14) = (int)&PTR_FUN_011250f4;
    
    // Advance the write pointer by 4 bytes.
    int *writePtr = (int *)(bufferBase + 0x14);
    *writePtr = *writePtr + 4;
    
    // Write the typeId (4 bytes) at the new location.
    bufferBase = (int *)*thisPtr; // Re-read buffer base (in case it changed? not really)
    **(int **)(bufferBase + 0x14) = typeId;
    
    // Prepare a 36-byte block on the stack from the 8-byte parameters and the extra int.
    char localBlock[36]; // actually the compiler placed them as separate local variables
    // The block is made up of data0 through data3 (each 8 bytes) and extra32 (4 bytes).
    // We'll copy from the parameters directly.
    // In the decompiled code: local_28 = data0, local_20 = data1, etc., and local_8 = extra32.
    // Total 8*4 + 4 = 36 bytes.
    
    // Align current write pointer to 4-byte boundary.
    char *alignedDst = (char *)((*(int *)(bufferBase + 0x14) + 7) & ~3);
    // Copy the 36 bytes.
    memcpy(alignedDst, (char *)&data0, 0x24); // &data0 matches local_28
    
    // Update write pointer to after the copied block.
    *(char **)(bufferBase + 0x14) = alignedDst + 0x24;
    
    // Write the 8-byte value (valueLow:valueHigh) after aligning again.
    int64 *valuePtr = (int64 *)((*(int *)(bufferBase + 0x14) + 0x27) & ~3);
    *(char **)(bufferBase + 0x14) = (char *)valuePtr;
    *valuePtr = ((int64)valueHigh << 32) | (int64)valueLow; // CONCAT44(valueHigh, valueLow)
    
    // Advance write pointer by 8 bytes.
    *(int *)(bufferBase + 0x14) = *(int *)(bufferBase + 0x14) + 8;
    
    return;
}