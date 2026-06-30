// FUN_004b8480: Buffer::writeObjectHeader

void __thiscall Buffer::writeObjectHeader(int *this, uint32 objectId, uint16 flags)
{
    uint8 *bufferPtr = *this; // This points to a pointer to the buffer structure. Dereference to get the buffer.
    // bufferPtr is a pointer to a buffer control block.
    // +0x14 in the buffer structure holds a pointer to the current write position.
    
    // Write vtable pointer (4 bytes) at current write position
    *(uint32 *)(bufferPtr + 0x14) = &PTR_LAB_011246e0; // Write object vtable
    (*(uint32 **)(bufferPtr + 0x14))++; // Advance write cursor by 4 bytes
    
    // Write object ID (4 bytes)
    *(uint32 *)(bufferPtr + 0x14) = objectId;
    (*(uint32 **)(bufferPtr + 0x14))++; // Advance by 4
    
    // Write flags (2 bytes)
    *(uint16 *)(bufferPtr + 0x14) = flags;
    // Advance write cursor by 5 and align to next 4-byte boundary
    *(uint32 *)(bufferPtr + 0x14) = ((uint32)(*(uint32 **)(bufferPtr + 0x14)) + 5U) & 0xFFFFFFFCU;
}