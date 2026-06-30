// FUNC_NAME: PacketBuffer::flushEntries(TempBuffer& src, int count)
void __thiscall PacketBuffer::flushEntries(TempBuffer& src, int count)
{
    // Adjust source buffer's write pointer backward by count * sizeof(entry) (8 bytes)
    int& srcWritePtr = *(int*)((int)&src + 8);
    srcWritePtr -= count * 8;

    int i = 0;
    if (count > 0) {
        do {
            // Get source entry from adjusted pointer
            int* srcEntry = (int*)(srcWritePtr + i * 8);
            // Get current destination write pointer (+0x08 in this object)
            int*& dstWritePtr = *(int**)((int)this + 8);
            // Copy 8-byte entry
            dstWritePtr[0] = srcEntry[0];
            dstWritePtr[1] = srcEntry[1];
            // Advance destination write pointer
            dstWritePtr += 2; // cast to int* increments by 4 bytes, so +2 = 8 bytes
            i++;
        } while (i < count);
    }
    return;
}