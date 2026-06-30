// FUNC_NAME: writeSerializedCommand
void writeSerializedCommand(int32 commandData, uint8 commandFlags) {
    // Get global serialization context pointer (DAT_01206880)
    int32* contextPtr = g_serializationContext; // g_serializationContext = *(int32*)0x01206880

    // Write vtable pointer for command type into buffer (current position pointed by contextPtr+0x14)
    *(void**)(*(int32*)(contextPtr + 0x14)) = &g_commandVTable; // PTR_LAB_01126b90

    // Advance buffer pointer by 4 bytes
    *(int32*)(contextPtr + 0x14) += 4;

    // Write a zero byte at the new buffer position (maybe padding or terminator)
    uint32* pBufferPtr = (uint32*)(contextPtr + 0x14);
    *(uint8*)(*pBufferPtr) = 0;

    // Align buffer pointer to next 4-byte boundary
    uint32* alignedPtr = (uint32*)((*pBufferPtr + 4) & 0xFFFFFFFC);
    *pBufferPtr = (uint32)alignedPtr;

    // Write commandData (4 bytes) at aligned position
    *alignedPtr = commandData;

    // Advance buffer pointer by 4 bytes
    *pBufferPtr += 4;

    // Write commandFlags (1 byte) at new position
    *(uint8*)(*pBufferPtr) = commandFlags;

    // Align buffer pointer again for next write
    *pBufferPtr = (*pBufferPtr + 4) & 0xFFFFFFFC;

    // Function returns void, buffer pointer in g_serializationContext+0x14 is updated
}