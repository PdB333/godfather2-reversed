// FUNC_NAME: DynamicArray16::reserve
// Function address: 0x005fc8f0
// Role: Resizes the internal buffer to at least newCapacity elements of 16 bytes each.
// Structure: this +0x00 = data pointer, +0x04 = count, +0x08 = capacity
// Uses malloc-like wrapper (FUN_009c8e80) and free (FUN_009c8f10).

void __thiscall DynamicArray16::reserve(uint newCapacity) {
    void *newBuffer;
    uint elementIndex;
    int byteOffset;
    void *oldBuffer;
    void *srcPtr;

    if (this->capacity < newCapacity) {
        newBuffer = (void *)FUN_009c8e80(newCapacity << 4); // Allocate newCapacity * 16 bytes
        if (this->data != 0) {
            elementIndex = 0;
            if (this->count != 0) {
                byteOffset = 0;
                do {
                    oldBuffer = this->data;
                    srcPtr = (void *)((int)oldBuffer + byteOffset);
                    if (newBuffer != 0) {
                        // Copy 16 bytes (two 8-byte chunks)
                        *(undefined8 *)newBuffer = *(undefined8 *)srcPtr;
                        *(undefined8 *)((int)newBuffer + 8) = *(undefined8 *)((int)srcPtr + 8);
                    }
                    elementIndex = elementIndex + 1;
                    byteOffset = byteOffset + 0x10;
                    newBuffer = (void *)((int)newBuffer + 0x10);
                } while (elementIndex < this->count);
            }
            FUN_009c8f10(this->data); // Free old buffer
        }
        this->data = newBuffer;
        this->capacity = newCapacity;
    }
}