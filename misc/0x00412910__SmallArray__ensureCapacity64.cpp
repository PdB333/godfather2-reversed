// FUNC_NAME: SmallArray::ensureCapacity64
void SmallArray::ensureCapacity64() {
    // Offset: +0x00 = buffer (int*)
    // Offset: +0x04 = count (uint)
    // Offset: +0x08 = capacity (uint)
    if (capacity < 0x40) {
        // Allocate space for 64 elements (512 bytes, each element 8 bytes)
        int* newBuffer = (int*)FUN_009c8e80(0x200);
        if (buffer != nullptr) {
            // Copy existing elements (8 bytes each)
            for (unsigned int i = 0; i < count; ++i) {
                newBuffer[i * 2] = buffer[i * 2];
                newBuffer[i * 2 + 1] = buffer[i * 2 + 1];
            }
            FUN_009c8f10(buffer); // Free old buffer
        }
        buffer = newBuffer;
        capacity = 0x40;
    }
}