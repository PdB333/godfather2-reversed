// FUNC_NAME: GhostBitStream::writeFloatBits
void GhostBitStream::writeFloatBits(float* inputFloats, int count) {
    uint32_t bitIndex = 0;
    for (int i = 0; i < count; i++) {
        int value = (int)(inputFloats[i] * DAT_0110ae44 + DAT_00e2cd54);
        
        // Ensure there is enough space in the bit buffer
        if (*(uint32_t*)(this + 0x30) < *(int32_t*)(this + 0x18) + 1U) {
            uint32_t newSize = (*(uint32_t*)(this + 0x30) + 8 >> 3) + 0x5dc;
            if (*(uint32_t*)(this + 0x10) < newSize) {
                if (*(char*)(this + 0x14) != '\0') {
                    *(uint32_t*)(this + 0x10) = newSize;
                    void* newBuffer = realloc(*(void**)(this + 0x0c), newSize);
                    *(void**)(this + 0x0c) = newBuffer;
                    *(uint32_t*)(this + 0x2c) = newSize * 8;
                    *(uint32_t*)(this + 0x30) = newSize * 8;
                    goto writeBit;
                }
            }
            else {
                *(uint32_t*)(this + 0x10) = newSize;
            }
            // Mark buffer as full? (maybe indicate overflow)
            *(char*)(this + 0x1c) = 1;
        }
        else {
writeBit:
            uint32_t currentBit = *(uint32_t*)(this + 0x18);
            if (value >= 0) {
                byte* bytePtr = (byte*)((currentBit >> 3) + *(int*)(this + 0x0c));
                *bytePtr = *bytePtr & ~(0x01 << ((byte)currentBit & 7));
            }
            else {
                byte* bytePtr = (byte*)(*(int*)(this + 0x0c) + (currentBit >> 3));
                *bytePtr = *bytePtr | 0x01 << ((byte)currentBit & 7);
            }
            *(int32_t*)(this + 0x18) = *(int32_t*)(this + 0x18) + 1;
            if (value < 0) {
                value = -value;
            }
        }
        int temp = value;
        FUN_0064b810(0x13, &temp); // Logging/debug call
    }
}