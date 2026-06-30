// FUNC_NAME: StreamWriter::writeMessage
void __thiscall StreamWriter::writeMessage(StreamWriter* this, int typeId, int data0, int64_t data1, int64_t data2) {
    // Get the base structure (assumed to be a vtable pointer at +0x0)
    int* base = *reinterpret_cast<int**>(this);
    // The current write pointer is at base + 0x14 (offset 0x14)
    // Write a 4-byte type tag (likely a class descriptor or vtable pointer)
    *reinterpret_cast<int*>(base[0x14]) = reinterpret_cast<int>(&PTR_LAB_01125194);
    // Advance pointer by 4
    base[0x14] += 4;

    // Write the 32-bit value (data0)
    *reinterpret_cast<int*>(base[0x14]) = data0;
    // Align pointer to next 4-byte boundary (round up to multiple of 4)
    base[0x14] = (base[0x14] + 7) & ~3;

    // Align pointer again for the following 64-bit writes (ensures alignment)
    int alignedPtr = (base[0x14] + 7) & ~3;
    base[0x14] = alignedPtr;
    // Write two 64-bit values consecutively
    *reinterpret_cast<int64_t*>(alignedPtr) = data1;
    *reinterpret_cast<int64_t*>(alignedPtr + 8) = data2;
    // Advance pointer by 16 bytes (two 64-bit values)
    base[0x14] = alignedPtr + 16;
}