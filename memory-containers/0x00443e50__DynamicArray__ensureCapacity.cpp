// FUNC_NAME: DynamicArray::ensureCapacity
class DynamicArray {
public:
    int* buffer;        // +0x00
    int   count;        // +0x04
    int   capacity;     // +0x08

    // Reallocates internal buffer to hold at least newCapacity elements (each 8 bytes).
    // Only grows; does nothing if newCapacity <= current capacity.
    void ensureCapacity(unsigned int newCapacity) {
        if ((unsigned int)this->capacity < newCapacity) {
            // Allocate new buffer for newCapacity * 8 bytes
            int* newBuffer = (int*)memoryAlloc(newCapacity * 8);  // FUN_009c8e80

            if (this->buffer != nullptr) {
                unsigned int i = 0;
                int* dest = newBuffer;

                // Copy only current count elements (each element is 8 bytes = 2 ints)
                if (this->count != 0) {
                    do {
                        if (dest != nullptr) {
                            int* src = this->buffer;
                            dest[0] = src[i * 2];       // first 4 bytes
                            dest[1] = src[i * 2 + 1];   // next 4 bytes
                        }
                        i++;
                        dest += 2;  // advance by element size (2 ints)
                    } while (i < (unsigned int)this->count);
                }

                // Free old buffer
                memoryFree(this->buffer);  // FUN_009c8f10
            }

            // Update pointer and capacity (count unchanged)
            this->buffer = newBuffer;
            this->capacity = newCapacity;
        }
    }
};