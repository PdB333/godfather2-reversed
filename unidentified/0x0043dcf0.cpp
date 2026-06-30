// FUN_0043dcf0: Array_28Bytes::reserveCapacity
// Reallocation function for a dynamic array of fixed-size elements (0x1c = 28 bytes each)
// Structure offsets:
//   +0x00: data pointer (int*)
//   +0x04: element count (int)
//   +0x08: capacity (int)
// This function ensures capacity >= newCapacity; if not, it allocates a new buffer,
// copies existing elements, and frees the old buffer.

class Array_28Bytes {
    int* data;       // +0x00
    int count;       // +0x04
    int capacity;    // +0x08

public:
    void __thiscall reserveCapacity(uint newCapacity) {
        if (capacity < newCapacity) {
            // Allocate new buffer: newCapacity * 28 bytes
            int* newData = (int*)allocateMemory(newCapacity * 0x1c);  // FUN_009c8e80
            
            if (data != nullptr) {
                // Copy existing elements into new buffer
                for (int i = 0; i < count; i++) {
                    // Copy 28 bytes (7 dwords) from oldData[i] to newData[i]
                    newData[i * 7 + 0] = data[i * 7 + 0];
                    newData[i * 7 + 1] = data[i * 7 + 1];
                    newData[i * 7 + 2] = data[i * 7 + 2];
                    newData[i * 7 + 3] = data[i * 7 + 3];
                    newData[i * 7 + 4] = data[i * 7 + 4];
                    newData[i * 7 + 5] = data[i * 7 + 5];
                    newData[i * 7 + 6] = data[i * 7 + 6];
                }
                // Free old buffer
                deallocateMemory(data);  // FUN_009c8f10
            }
            
            // Update members
            data = newData;
            capacity = newCapacity;
        }
    }
};

// Note: allocateMemory and deallocateMemory are external functions (likely custom allocators)
extern int* allocateMemory(int size);
extern void deallocateMemory(int* ptr);