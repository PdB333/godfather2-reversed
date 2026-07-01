// FUNC_NAME: DynamicArray::reserve
// Function address: 0x008e5cf0
// Role: Reserves capacity for a dynamic array of 32-bit elements. If the requested capacity exceeds the current capacity,
// it allocates a new buffer, copies existing elements, frees the old buffer, and updates the capacity. Otherwise, does nothing.

// External allocator and deallocator functions (likely custom memory manager).
extern "C" void* FUN_009c8e80(uint sizeBytes);
extern "C" void  FUN_009c8f10(void* ptr);

// Dynamic array structure (typical for EA EARS containers)
class DynamicArray {
public:
    int* data;       // +0x00 pointer to elements (4 bytes each)
    int  size;       // +0x04 number of elements currently stored
    int  capacity;   // +0x08 allocated capacity (number of elements)

    // Reserve new capacity; only expands, never shrinks.
    void __thiscall reserve(uint newCapacity) {
        if ((uint)capacity < newCapacity) {
            // Allocate new buffer (raw bytes = newCapacity * sizeof(int))
            int* newData = (int*)FUN_009c8e80(newCapacity * 4);

            // Copy existing elements if old buffer exists
            if (data != 0) {
                for (uint i = 0; i < (uint)size; i++) {
                    newData[i] = data[i];
                }
                // Deallocate old buffer
                FUN_009c8f10(data);
            }

            // Update pointer and capacity
            data = newData;
            capacity = (int)newCapacity;
        }
    }
};