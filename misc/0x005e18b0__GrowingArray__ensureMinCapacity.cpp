// FUNC_NAME: GrowingArray::ensureMinCapacity
// Reconstructed from 0x005e18b0 - Ensures internal buffer capacity >= 20 (0x14)
// Structure offsets:
//   +0x00: buffer (int*) - pointer to element array
//   +0x04: size (int)    - number of elements currently stored
//   +0x08: capacity (int) - allocated element count (each 4 bytes)
void __thiscall ensureMinCapacity(void* this) {
    int* buffer = *(int**)this;            // +0x00
    int size = *(int*)((char*)this + 4);   // +0x04
    int capacity = *(int*)((char*)this + 8); // +0x08

    if (capacity < 20) {
        // Allocate new buffer for 20 elements (0x50 = 20 * 4)
        int* newBuffer = (int*)FUN_009c8e80(0x50);
        if (buffer != 0 && size != 0) {
            for (uint i = 0; i < (uint)size; i++) {
                if (newBuffer != 0) {
                    newBuffer[i] = buffer[i];
                }
            }
        }
        if (buffer != 0) {
            FUN_009c8f10(buffer);
        }
        *(int**)this = newBuffer;
        *(int*)((char*)this + 8) = 20; // new capacity
    }
    return;
}