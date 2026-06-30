// FUNC_NAME: EARSString::EARSString (constructor)

// EARSString: small-string-optimized string class
// Offsets (relative to this pointer):
// +0x00 : vtable pointer
// +0x0C : union { char smallBuf[16]; char* heapBuf; }  // small string buffer or pointer to heap buffer
// +0x1C : int length
// +0x20 : int capacity

class EARSString {
public:
    void** vtable;          // +0x00
    // +0x04..0x0B: unknown padding/fields (not used here)
    union {
        char smallBuf[16];  // small buffer (used when capacity <= 15)
        char* heapBuf;      // pointer to heap-allocated buffer (when capacity > 15)
    } _buffer;              // +0x0C
    int length;             // +0x1C
    int capacity;           // +0x20

    // Constructor: initializes an empty string with small buffer (capacity 15)
    __thiscall EARSString() {
        // Temporarily set vtable to construction vtable (base class vtable)
        this->vtable = &PTR_FUN_00da9810;

        // If the object was previously holding a heap-allocated buffer, free it
        if (this->capacity > 15) {
            // Free the old heap buffer (function at 0x009c8eb0 takes pointer to buffer)
            FUN_009c8eb0(this->_buffer.heapBuf);
        }

        // Reset to empty small string state
        this->capacity = 15;             // Reset capacity to small buffer size
        this->length = 0;                // String is empty
        this->_buffer.smallBuf[0] = '\0'; // Null-terminate the small buffer

        // Set final vtable (derived class or self vtable)
        this->vtable = &PTR_LAB_00e31044;
    }
};