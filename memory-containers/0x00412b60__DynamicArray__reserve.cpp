// FUNC_NAME: DynamicArray::reserve
// Function at 0x00412b60
// Reallocates internal buffer to at least newCapacity elements (each 4 bytes).
// Class layout (DynamicArray):
//   +0x00: int* data (pointer to array of ints)
//   +0x04: int size   (number of elements currently stored)
//   +0x08: int capacity (allocated capacity in elements)
// Uses EA EARS custom allocator (FUN_009c8e80 = alloc, FUN_009c8f10 = free)

void __thiscall DynamicArray::reserve(uint newCapacity)
{
    int* oldData;
    uint i;
    int* newData;

    if ((uint)this->capacity < newCapacity) {
        // Allocate new buffer
        newData = (int*)FUN_009c8e80(newCapacity * 4);
        if (this->data != 0) {
            // Copy existing elements
            i = 0;
            if (this->size != 0) {
                do {
                    if (newData != 0) {
                        newData[i] = this->data[i];
                    }
                    i = i + 1;
                } while (i < (uint)this->size);
            }
            // Free old buffer
            FUN_009c8f10(this->data);
        }
        // Update pointers and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
    return;
}