// FUNC_NAME: WriteStream::writePackedObject
// Function at 0x0048ccc0: Writes a tagged object (vtable pointer) followed by 8-byte and 4-byte data fields into a stream buffer.
// Stream layout: this[0] points to a data block; that data block's +0x14 holds the current write pointer.
void __thiscall WriteStream::writePackedObject(int param2, int param3, int param4)
{
    int* pDataBlock = *reinterpret_cast<int**>(this); // dereference this to get the data block pointer
    // Write the type tag (pointer to vtable/function table)
    *reinterpret_cast<void***>(pDataBlock + 0x14) = &PTR_FUN_01123ddc;
    // Advance write pointer by 4 bytes (size of the tag)
    int* writePos = *reinterpret_cast<int**>(pDataBlock + 0x14);
    writePos += 1; // advance by 1 int (4 bytes)
    *reinterpret_cast<int**>(pDataBlock + 0x14) = writePos;
    // Align the write pointer to the next 4-byte boundary
    pDataBlock = *reinterpret_cast<int**>(this); // re-read after potential change
    writePos = *reinterpret_cast<int**>(pDataBlock + 0x14);
    writePos = reinterpret_cast<int*>((reinterpret_cast<int>(writePos) + 3) & ~3);
    *reinterpret_cast<int**>(pDataBlock + 0x14) = writePos;
    // Write the 8-byte value (param2:param3 combined)
    *reinterpret_cast<__int64*>(writePos) = (static_cast<__int64>(param3) << 32) | static_cast<unsigned int>(param2);
    // Write the 4-byte value (param4) at offset 8
    writePos[2] = param4; // offset 8 bytes (2 ints)
    // Advance write pointer by 12 bytes (8+4)
    *reinterpret_cast<int**>(pDataBlock + 0x14) = writePos + 3; // 3 ints = 12 bytes
}