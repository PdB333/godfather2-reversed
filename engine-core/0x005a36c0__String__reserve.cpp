// FUNC_NAME: String::reserve
// Address: 0x005a36c0
// Resizes the internal buffer to accommodate at least newCapacity elements.
// Uses small buffer optimization when possible.

class String {
public:
    int mSize;          // +0x00: number of elements (used?)
    int mCapacity;      // +0x04: allocated capacity
    char* mBuffer;      // +0x08: pointer to data (inline or heap)
    // +0x0C: inline buffer starts here (size depends on class layout)

    void __thiscall reserve(int newCapacity);
};

// Forward declarations for helper functions (from EARS engine)
extern "C" {
    char* allocateBuffer(int something);              // FUN_005a16d0
    void copyBufferContents(char* dest, char* src);   // FUN_005a3420 (copy element count * 0x20 bytes)
    void initializeString(void* memory);               // FUN_005a1000 (zero-initialize a temporary String)
    void destroyString(void* ptr);                     // DAT_0119caf4 (destructor for temporary)
}

void String::reserve(int newCapacity) {
    // Only grow if requested capacity is larger than current
    if (newCapacity > mCapacity) {
        if (newCapacity < 2) {
            // Clamp to 2? Actually the original code returns if < 2? Let's keep the logic:
            mCapacity = newCapacity;
            return;
        }
        
        // Allocate a new buffer (the argument 0 might indicate default alignment/arena)
        char* newBuffer = allocateBuffer(0);
        
        // Copy existing data: size * elementSize (elementSize assumed 0x20 = 32 bytes)
        copyBufferContents(newBuffer, mBuffer);  // Copies mSize * 0x20 bytes
        
        // Update capacity
        mCapacity = newCapacity;
        
        // Free old buffer if it was heap-allocated (inline buffer check)
        if ((int*)mBuffer != (this + 3)) {  // Inline buffer starts at offset 12
            allocateBuffer((int*)mBuffer);  // Actually this frees? The original calls FUN_005a16d0 again (maybe for free)
            // Note: This might be a different overload; in our reconstruction we interpret as free.
        }
        
        // Set the buffer to the new allocation
        mBuffer = newBuffer;
        
        // Use a temporary stack-based String to handle small-buffer cleanup or something
        struct TempString {
            int pad0;      // 0x00
            int pad1;      // 0x04
            int pad2;      // 0x08
            char data[8];  // 0x0C (inline buffer for temporary)
        } temp;
        memset(&temp, 0, sizeof(temp));  // Zero-initialize
        temp.pad2 = (int)&temp.data;     // Points to its own inline buffer
        
        initializeString(&temp);  // Possibly sets up a small-buffer view
        
        // After initialization, check if the temporary's buffer pointer changed
        // If it's not pointing to its inline data, free it.
        if ((int*)temp.pad2 != (int*)(&temp.data) && (int*)temp.pad2 != nullptr) {
            destroyString((int*)temp.pad2);
        }
    }
    // else: no action needed if newCapacity <= current capacity
}