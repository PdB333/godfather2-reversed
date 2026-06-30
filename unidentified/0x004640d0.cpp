// FUN_004640d0: StreamPool::initialize(unsigned int bufferBitSize)
undefined4* StreamPool::initialize(undefined4* this, uint bufferBitSize) {
    uint originalSize = bufferBitSize;
    this[0] = 0;
    this[1] = 0;
    undefined4** slotArray = (undefined4**)(this + 2);
    int numSlots = 8;
    do {
        // Allocate a new stream object (12 bytes)
        int* streamObj = (int*)malloc(0xc);
        if (streamObj != nullptr) {
            if (originalSize == 0) {
                streamObj[1] = 0;
                *(short*)(streamObj + 2) = 0;
                *streamObj = 0;
            } else {
                // Store the buffer bit size
                streamObj[1] = originalSize;
                // Compute byte size: (originalSize + 7) / 8
                short byteSize = (short)(originalSize >> 3);
                if ((originalSize & 7) != 0) {
                    byteSize = byteSize + 1;
                }
                *(short*)(streamObj + 2) = byteSize;
                // Allocate the actual buffer
                char* buffer = (char*)malloc((short)streamObj[2]);
                *streamObj = (int)buffer;
                if (buffer != nullptr && (short)streamObj[2] != 0) {
                    // Zero-initialize the buffer
                    for (uint i = 0; i < (ushort)streamObj[2]; i++) {
                        buffer[i] = 0;
                    }
                }
            }
        }
        *slotArray = (undefined4*)streamObj;
        slotArray++;
        numSlots--;
    } while (numSlots != 0);
    return this;
}