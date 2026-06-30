// FUNC_NAME: BufferWriter::writeObjectRecord

void __thiscall BufferWriter::writeObjectRecord(int *thisPtr, uint32_t typeId, const uint128_t *guid, uint32_t value)
{
    // thisPtr points to a BufferWriter object. Its first field is a pointer to a buffer control block.
    int *bufferControl = (int *)*thisPtr; // dereference this to get control block base
    
    // bufferControl+0x14 points to current write pointer (a pointer to the next free location)
    // store vtable pointer at current location
    *(uint32_t **)(*bufferControl + 0x14) = (uint32_t *)&PTR_LAB_01124b94; // vtable for this object type
    
    // advance write pointer by 4 bytes
    int *writePtrPtr = (int *)(bufferControl + 0x14);
    *writePtrPtr = (int)((char *)*writePtrPtr + 4);
    
    // re-read buffer control (not strictly necessary)
    bufferControl = (int *)*thisPtr;
    
    // write typeId at the new current location
    *(uint32_t *)(*(int*)(bufferControl + 0x14)) = typeId;
    
    // align current write pointer to next 16-byte boundary
    uint64_t *alignedPtr = (uint64_t *)((*(int*)(bufferControl + 0x14) + 0x13) & 0xFFFFFFF0);
    *(uint64_t **)(bufferControl + 0x14) = alignedPtr; // store aligned pointer
    
    // copy 16-byte GUID into aligned location
    *alignedPtr = *guid;
    alignedPtr[1] = guid[1];
    
    // write value at offset 0x10 from aligned base (after GUID)
    int currentOffset = *(int *)(bufferControl + 0x14);
    *(uint32_t *)(currentOffset + 0x10) = value;
    
    // advance write pointer by 20 bytes (0x14) from aligned base
    *(int *)(bufferControl + 0x14) = currentOffset + 0x14;
}