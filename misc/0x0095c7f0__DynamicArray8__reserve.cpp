// FUNC_NAME: DynamicArray8::reserve

// Comment: Function at 0x0095c7f0 - resize capacity for dynamic array of 8-byte elements
// Structure layout:
//   +0x00: int* data       // pointer to array of 8-byte elements
//   +0x04: int  count      // number of elements currently stored
//   +0x08: int  capacity   // allocated capacity (max elements before reallocation)

extern void* J__alloc(uint size);   // FUN_009c8e80 - custom memory allocation
extern void  J__free(void* ptr);    // FUN_009c8f10 - custom memory deallocation

void __thiscall DynamicArray8::reserve(uint newCapacity) {
    if ((uint)capacity < newCapacity) {
        int* newData = (int*)J__alloc(newCapacity * 8);
        if (data != 0) {
            uint i = 0;
            int* dst = newData;
            if (count != 0) {
                do {
                    if (newData != 0) {
                        dst[0] = data[i * 2];
                        dst[1] = data[i * 2 + 1];
                    }
                    i++;
                    dst += 2;
                } while (i < (uint)count);
            }
            J__free(data);
        }
        data = newData;
        capacity = newCapacity;
    }
}