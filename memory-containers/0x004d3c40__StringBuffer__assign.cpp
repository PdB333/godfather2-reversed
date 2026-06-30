// FUNC_NAME: StringBuffer::assign
// Function at 0x004d3c40: Assigns a copy of a data buffer to a StringBuffer object.
// Allocates memory, copies data, appends null terminator, and stores a custom deallocator.
#include <cstring> // for memcpy

// Forward declaration of allocator functions
void* allocate(size_t size);           // FUN_009c8e50 - custom memory allocator
void  customDeallocator(void* ptr);    // FUN_009c8eb0 (thunk) - custom memory deallocator

class StringBuffer {
public:
    char*  buffer;      // +0x00: pointer to owned buffer
    int32_t length;     // +0x04: number of characters (excluding null terminator)
    int32_t capacity;   // +0x08: allocated size (including null terminator)
    void  (*deallocator)(void*); // +0x0C: function pointer to deallocate the buffer

    // Copy the given data (param_2) of size param_3 into this StringBuffer.
    // If size is zero, the buffer is cleared without allocation.
    void assign(const void* src, int32_t size) {
        if (size != 0) {
            this->length   = size;
            this->capacity = size;
            this->buffer   = (char*)allocate(size + 1); // allocate extra byte for null terminator
            std::memcpy(this->buffer, src, size);
            this->buffer[size] = '\0';
            this->deallocator = customDeallocator;
        } else {
            this->buffer   = nullptr;
            this->capacity = 0;
            this->length   = 0;
        }
    }
};