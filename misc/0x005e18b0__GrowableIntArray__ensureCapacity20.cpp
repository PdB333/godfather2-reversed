// FUNC_NAME: GrowableIntArray::ensureCapacity20
// Address: 0x005e18b0
// Role: Ensures the internal array has capacity for at least 20 elements (20 * 4 = 80 bytes).
// If current capacity < 20, allocates a new buffer, copies existing elements, frees old buffer,
// and updates capacity to 20.  Part of a simple growable array of 32-bit values (int/uint).

#include <cstdint>

// Memory allocation wrappers (likely from EARS engine)
extern void* __cdecl _alloc(uint32_t size);
extern void __cdecl _free(void* ptr);

class GrowableIntArray {
public:
    int*     data;      // +0x00: pointer to dynamic array
    int32_t  count;     // +0x04: number of elements currently stored
    int32_t  capacity;  // +0x08: allocated capacity (number of ints)

    void ensureCapacity20() {
        if (this->capacity < 20) {
            int* newData = (int*)_alloc(80); // 20 * sizeof(int) = 80 bytes
            if (this->data != nullptr) {
                if (this->count != 0) {
                    // Copy existing elements
                    int i = 0;
                    do {
                        newData[i] = this->data[i];
                        i++;
                    } while (i < this->count);
                }
                _free(this->data);
            }
            this->data     = newData;
            this->capacity = 20;
        }
    }
};