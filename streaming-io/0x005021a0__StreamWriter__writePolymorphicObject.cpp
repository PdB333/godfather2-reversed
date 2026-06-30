// FUNC_NAME: StreamWriter::writePolymorphicObject

void __thiscall StreamWriter::writePolymorphicObject(char *this, int32_t val1, int64_t val2, int64_t val3, int32_t val4, int32_t val5)
{
    // this+0 is a pointer to a buffer header (BufferHeader*)
    BufferHeader* bufferHeader = *(BufferHeader**)this;  // +0x00: pointer to buffer header
    char** writePtr = &bufferHeader->m_writePtr;          // +0x14: current write pointer inside buffer

    // Write vtable pointer of the object being serialized
    **(int**)(writePtr) = (int)&PTR_FUN_01124f6c;        // Write vtable address
    *writePtr += 4;                                       // Advance write pointer

    bufferHeader = *(BufferHeader**)this;                 // Re-fetch (unnecessary, offset unchanged)
    **(int**)(writePtr) = val1;                           // Write first int32 parameter
    // Align write pointer to 4-byte boundary for 8-byte writes (round up with +7 & ~3)
    int64_t* alignedPtr = (int64_t*)((*(int*)(writePtr) + 7) & 0xFFFFFFFC);
    *writePtr = (char*)alignedPtr;                        // Update write pointer to aligned address
    alignedPtr[0] = val2;                                 // Write two 8-byte values
    alignedPtr[1] = val3;

    // Align again to 4-byte boundary (using +0x13 & ~3)
    int64_t* alignedPtr2 = (int64_t*)((*(int*)(writePtr) + 0x13) & 0xFFFFFFFC);
    *writePtr = (char*)alignedPtr2;
    *alignedPtr2 = (int64_t)(((uint64_t)(uint32_t)val5 << 32) | (uint32_t)val4);  // Combine val4 and val5 into 64-bit value

    *writePtr += 8;                                       // Advance past the last written 8 bytes
}