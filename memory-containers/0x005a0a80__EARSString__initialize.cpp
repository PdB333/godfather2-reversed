// FUNC_NAME: EARSString::initialize
// Address: 0x005a0a80
// This function initializes an EARSString with small string optimization (SSO).
// It sets capacity to 8, size to 8, and points the data pointer to the inline buffer.
// The inline buffer is zeroed out. If capacity > 15, it would allocate heap memory.

class EARSString {
public:
    int capacity;             // +0x00
    int size;                 // +0x04
    char* data;               // +0x08
    char inlineBuffer[16];    // +0x0C (offsets 0x0C to 0x1C)

    void initialize();
};

void EARSString::initialize()
{
    // Point to the inline buffer (starts at offset 0x0C)
    char* buf = inlineBuffer;

    capacity = 8;
    size = 8;
    data = buf;

    // Clear first 8 bytes of inline buffer (two ints)
    *reinterpret_cast<int*>(buf) = 0;
    *reinterpret_cast<int*>(buf + 4) = 0;

    // Clear bytes at offset 8 and 12 of inline buffer (offsets 0x14 and 0x18)
    *reinterpret_cast<int*>(buf + 8) = 0;
    *reinterpret_cast<int*>(buf + 12) = 0;

    // Call to pool/allocator initialization (function address 0x0059c140)
    // May be: Allocator::initialize(1);
    FUN_0059c140(1);

    // If capacity > 15, allocate heap memory
    if (capacity > 15) {
        int* heapBuf = reinterpret_cast<int*((*func_ptr)(capacity + 1, 0))(DAT_0119caf0, capacity + 1, 0);
        data = reinterpret_cast<char*>(heapBuf);
    }

    // Zero-fill data buffer up to capacity
    for (int i = 0; i < capacity; ++i) {
        data[i] = 0;
    }

    // Null-terminate at position capacity
    data[capacity] = 0;

    // Update size to equal capacity (already set above)
    size = capacity;
}