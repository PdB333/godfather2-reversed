// FUNC_NAME: BufferWriter::writeTypedDataBlock
void __thiscall BufferWriter::writeTypedDataBlock(void* thisPtr, uint32_t typeId, const uint64_t data[2]) {
    // Offsets: +0x14 = uint8_t* currentWritePtr (points into internal buffer)
    uint8_t** currentPtr = reinterpret_cast<uint8_t**>(reinterpret_cast<uint32_t>(thisPtr) + 0x14);
    uint8_t* base = *currentPtr;

    // Write a 4-byte vtable pointer (likely for serialized type tag)
    *(uint32_t*)base = reinterpret_cast<uint32_t>(&PTR_LAB_01124ab8);  // vtable for this data type
    *currentPtr = base + 4;

    // Write the 4-byte type identifier
    *(uint32_t*)(*currentPtr) = typeId;
    *currentPtr = *currentPtr + 4;

    // Align next write to 16 bytes
    uint64_t* aligned = reinterpret_cast<uint64_t*>( (reinterpret_cast<uint32_t>(*currentPtr) + 0x13) & 0xFFFFFFF0 );

    // Write 16 bytes (128-bit data, likely a GUID or Vec4)
    aligned[0] = data[0];
    aligned[1] = data[1];

    // Update write pointer past the 16-byte block
    *currentPtr = reinterpret_cast<uint8_t*>(aligned + 2);
}