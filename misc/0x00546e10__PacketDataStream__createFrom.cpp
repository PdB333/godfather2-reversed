// FUNC_NAME: PacketDataStream::createFrom
int PacketDataStream::createFrom(int param_1, int* sourceObj)
{
    // Get thread-local allocator context (unused result)
    TlsGetValue(DAT_01139810);

    // Allocate a new PacketDataStream object (0x1c bytes, pool tag 0xb)
    int* pStream = (int*)FUN_00aa2680(0x1c, 0xb);
    *(short*)(pStream + 1) = 0x1c; // +0x4: stored allocation size (16-bit)

    // Get the current network session/interface
    int* session = (int*)FUN_00bedf00();

    // Call virtual function at offset 0x220 on sourceObj to get required data size
    int requiredSize = (*(int(**)(void))(*(int*)sourceObj + 0x220))();

    // Current capacity of the new stream (at +0x18), mask off high bits
    int currentCapacity = *(int*)(pStream + 6) & 0x3fffffff; // +0x18

    // Ensure buffer is large enough
    if (currentCapacity < requiredSize) {
        int newCapacity = currentCapacity * 2;
        if (newCapacity <= requiredSize) {
            newCapacity = requiredSize;
        }
        // Reallocate the internal buffer pointer at +0x10
        FUN_00aa4110(pStream + 4, newCapacity, 1); // +0x10: buffer pointer
    }

    // Set used size and a global timestamp/sequence from DAT_00e4458c
    *(int*)(pStream + 5) = requiredSize;  // +0x14: used size
    *(int*)(pStream + 3) = DAT_00e4458c;  // +0xc: stream metadata

    // Initialize stream content from sourceObj
    FUN_00546ec0(pStream, sourceObj);

    return (int)pStream;
}