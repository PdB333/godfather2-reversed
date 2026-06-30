// FUNC_NAME: PacketBuffer::clear
extern void freeMemory(void* ptr);

void __thiscall PacketBuffer::clear(int* thisPtr) {
    int state = thisPtr[0]; // +0x00: buffer state (5/6 = allocated)
    void* buffer = (void*)thisPtr[2]; // +0x08: pointer to allocated memory
    int bufferSize = thisPtr[3]; // +0x0C: size of allocated memory

    if ((state == 5 || state == 6) && buffer != nullptr) {
        freeMemory(buffer); // release allocation
        memset(buffer, 0, bufferSize); // zero fill to prevent leaks
        thisPtr[0] = 0; // reset state
        thisPtr[1] = 0; // +0x04: reset size field (likely used size)
        thisPtr[4] = 0; // +0x10: reset flags or offset
    }
}