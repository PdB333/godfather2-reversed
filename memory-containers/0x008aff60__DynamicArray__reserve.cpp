// FUNC_NAME: DynamicArray::reserve
// Reconstructed from Ghidra at address 0x008aff60
// Grows the internal data array to at least 'newCapacity' elements.
// Only executes if current capacity is less than requested capacity.
// Structure offsets:
// +0x00: data (int*) - pointer to allocated array
// +0x04: size  (uint) - number of elements currently used
// +0x08: capacity (uint) - number of elements allocated

struct DynamicArray {
    int* data;
    unsigned int size;
    unsigned int capacity;
};

// External allocation and deallocation routines (likely malloc/free)
void* __cdecl allocate(unsigned int size);
void  __cdecl deallocate(void* ptr);

void __thiscall DynamicArray::reserve(unsigned int newCapacity)
{
    if (capacity < newCapacity) {
        int* newData = (int*)allocate(newCapacity * sizeof(int));
        if (data != 0) {
            unsigned int i = 0;
            int* dest = newData;
            if (size != 0) {
                do {
                    // Null check on destination (decompiler artifact, kept for fidelity)
                    if (dest != 0) {
                        *dest = data[i];
                    }
                    i++;
                    dest++;
                } while (i < size);
            }
            deallocate(data);
        }
        data = newData;
        capacity = newCapacity;
    }
}