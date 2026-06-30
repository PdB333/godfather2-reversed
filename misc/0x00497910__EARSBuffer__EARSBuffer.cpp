// FUNC_NAME: EARSBuffer::EARSBuffer
class EARSBuffer {
public:
    // +0x00: vtable pointer
    // +0x04..0x18: unknown (7 fields of 4 bytes each)
    // +0x1C: buffer pointer (allocated at runtime)
    // +0x20: current count
    // +0x24: maximum capacity (or block count)
    void* vtable;
    char pad_04[0x18];        // filler for unknown fields
    char* buffer;             // +0x1C
    int count;               // +0x20
    int capacity;            // +0x24

    // Constructor takes a vtable pointer and initializes a fixed-size memory pool
    __thiscall EARSBuffer(void* vtable) {
        // Store the vtable pointer (for RTTI or virtual dispatch)
        this->vtable = vtable;

        // Compute exponent from magic constant 0x10 (16)
        // This likely determines a size class or block size index
        int exponent = 1;
        unsigned int val = 0x10;
        do {
            exponent++;
            val >>= 2;
        } while (val != 0);
        // exponent = 4 (log2(0x10) = 4)
        InitializeBlockSizes(exponent);  // FUN_00498a70

        // Allocate a buffer of 0x300 (768) bytes for storing elements
        buffer = (char*)AllocateMemory(0x300);  // FUN_009c8e80

        // Initialize usage tracking
        count = 0;          // no elements yet
        capacity = 0x40;    // maximum allowed elements (or fixed block count)
    }
};