// FUNC_NAME: ByteBuffer::append

#include <cstddef>
#include <cstring>

// External allocator functions (EA EARS engine)
void* allocateBytes(size_t size);
void  deallocateBytes(void* ptr);

// ByteBuffer structure at +0x00
// +0x00: char* data         (pointer to data)
// +0x04: int size           (current used size)
// +0x08: int capacity       (allocated capacity)
// +0x0C: void (*dealloc)(void*)  (custom deallocation function)

struct ByteBuffer {
    char*  data;      // +0x00
    int    size;      // +0x04
    int    capacity;  // +0x08
    void (*dealloc)(void*); // +0x0C
};

// Forward declaration of the initialization function used when buffer is empty
int* __thiscall ByteBuffer::initializeWithData(int srcBase, int srcOffset, size_t length);

int* __thiscall ByteBuffer::append(int srcBase, int srcOffset, size_t length) {
    int currentSize = this->size;
    if (currentSize != 0) {
        size_t newSize = currentSize + length;
        if (newSize < (size_t)this->capacity) {
            // Enough space – just copy additional data
            memcpy(this->data + currentSize, reinterpret_cast<const void*>(srcBase + srcOffset), length);
        } else {
            // Need to reallocate a larger buffer
            char* newData = static_cast<char*>(allocateBytes(newSize + 1)); // +1 for null terminator
            // Copy existing data
            memcpy(newData, this->data, currentSize);
            // Append new data
            memcpy(newData + currentSize, reinterpret_cast<const void*>(srcBase + srcOffset), length);
            // Free old buffer if a deallocator is set
            if (this->data != nullptr) {
                this->dealloc(this->data);
            }
            this->data     = newData;
            this->capacity = static_cast<int>(newSize);
            this->dealloc  = deallocateBytes;  // Use standard deallocator after reallocation
        }
        this->size = currentSize + static_cast<int>(length);
        // Null-terminate the buffer (string compatibility)
        *(this->data + this->size) = '\0';
        return reinterpret_cast<int*>(this);
    } else {
        // Buffer is empty – delegate to initialization function
        return this->initializeWithData(srcBase, srcOffset, length);
    }
}