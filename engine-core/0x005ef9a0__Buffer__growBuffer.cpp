// FUNC_NAME: Buffer::growBuffer
// Address: 0x005ef9a0
// Reallocates the internal buffer to hold 16 elements (each 12 bytes) when current capacity is insufficient.

void Buffer::growBuffer() {
    // Check if current capacity is less than 16
    if (this->capacity < 16) {
        // Allocate new buffer for 16 elements of 12 bytes each (192 bytes total)
        void* newBuffer = allocateMemory(192); // 0xC0

        if (this->buffer != nullptr) {
            // Copy existing elements from old buffer to new buffer (each element is 12 bytes)
            uint count = this->count;
            if (count != 0) {
                int srcOffset = 0;
                byte* dst = (byte*)newBuffer;
                do {
                    // Copy 12 bytes per element (first 8 bytes + next 4 bytes)
                    *(undefined8*)dst = *(undefined8*)((byte*)this->buffer + srcOffset);
                    *(undefined4*)(dst + 8) = *(undefined4*)((byte*)this->buffer + srcOffset + 8);
                    srcOffset += 12; // 0xC
                    dst += 12;
                    count--;
                } while (count != 0);
            }
            // Free the old buffer
            freeMemory(this->buffer);
        }

        // Update buffer pointer and capacity
        this->buffer = newBuffer;
        this->capacity = 16;
    }
}