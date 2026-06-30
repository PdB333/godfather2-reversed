// FUNC_NAME: StreamWriter::appendAligned
void __thiscall StreamWriter::appendAligned(int *this, unsigned int param2, const __m128i *param3, const __m128i *param4)
{
    // this points to a StreamWriter object where *this is a pointer to internal buffer structure
    int *bufferStruct = reinterpret_cast<int *>(*this);
    
    // bufferStruct points to a structure with a write pointer at offset 0x14
    // Write the global vtable pointer (type identifier) at the current write position
    *reinterpret_cast<int*>(bufferStruct[0x14 / 4]) = reinterpret_cast<int>(&PTR_LAB_0110b7ac);
    
    // Advance the write pointer by 4 bytes (size of the pointer)
    int *writePtrPtr = &bufferStruct[0x14 / 4];
    *writePtrPtr = *writePtrPtr + 4;
    
    // Write param2 (32-bit) at the new write position
    *reinterpret_cast<int*>(bufferStruct[0x14 / 4]) = param2;
    
    // Align the write pointer to a 16-byte boundary with a minimum skip of 16 bytes
    // Formula: (current + 0x13) & 0xfffffff0
    int writePtr = bufferStruct[0x14 / 4];
    int alignedPtr = (writePtr + 0x13) & 0xfffffff0;
    bufferStruct[0x14 / 4] = alignedPtr;
    
    // Write the two 64-bit values (128-bit total) from param3 and param4
    __m128i *dst = reinterpret_cast<__m128i*>(alignedPtr);
    dst[0] = *param3;
    dst[1] = *param4;
    
    // Advance write pointer by the 16 bytes written
    bufferStruct[0x14 / 4] += 0x10;
}