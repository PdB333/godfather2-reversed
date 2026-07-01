// FUNC_NAME: DynamicArray::reserve

// Reconstructed from address 0x0098f4c0
// This function ensures the dynamic array has at least 'newCapacity' slots.
// Element size is 8 bytes (likely a pair of ints or a struct).
// Structure fields: [0] = data pointer, [1] = current size, [2] = allocated capacity (both in element count, not bytes)

class DynamicArray {
public:
    int* data;       // +0x00
    int  size;       // +0x04
    int  capacity;   // +0x08

    void __thiscall reserve(uint newCapacity) {
        if ((uint)capacity < newCapacity) {
            int* newData = (int*)allocate(newCapacity * 8);  // FUN_009c8e80
            if (data != 0) {
                uint count = 0;
                int* dst = newData;
                if (size != 0) {
                    do {
                        if (dst != 0) {
                            // Copy one 8-byte element
                            dst[0] = *(int*)(data + count * 2);
                            dst[1] = *(int*)(data + count * 2 + 1);
                        }
                        count++;
                        dst += 2;
                    } while (count < (uint)size);
                }
                deallocate(data);  // FUN_009c8f10
            }
            data = newData;
            capacity = newCapacity;
        }
    }

private:
    // Stubs for allocation/deallocation (actual addresses: 0x009c8e80, 0x009c8f10)
    static int* allocate(int bytes);
    static void deallocate(int* ptr);
};