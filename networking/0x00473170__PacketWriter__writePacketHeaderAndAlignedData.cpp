// FUNC_NAME: PacketWriter::writePacketHeaderAndAlignedData
void __thiscall PacketWriter::writePacketHeaderAndAlignedData(int a, int b, int c, void* data, int count, int alignment)
{
    // Current write pointer stored at this+0x14
    int* writePtr = *(int**)(this + 0x14);  // +0x14: current write pointer

    // Write header: first 3 integers
    *writePtr = a;
    writePtr = (int*)((int)writePtr + 4);
    *writePtr = b;
    writePtr = (int*)((int)writePtr + 4);
    *writePtr = c;
    writePtr = (int*)((int)writePtr + 4);
    *writePtr = count;
    writePtr = (int*)((int)writePtr + 4);
    *writePtr = alignment;
    writePtr = (int*)((int)writePtr + 4);

    // Align destination for data to next multiple of 'alignment' bytes
    // The formula: (writePtr + alignment + 3) & ~(alignment - 1)
    int aligned = ((int)writePtr + alignment + 3) & ~(alignment - 1);
    void* dst = (void*)aligned;
    *(int**)(this + 0x14) = (int*)dst;

    // Copy data array (count * 4 bytes)
    memcpy(dst, data, count * 4);

    // Advance write pointer past the data
    *(int**)(this + 0x14) = (int*)((int)dst + count * 4);
}