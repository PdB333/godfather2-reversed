// FUNC_NAME: DynamicArray8::reserve
// Function address: 0x00461e30
// Role: Resizes the internal buffer of a dynamic array with 8-byte elements.
// The object layout:
//   +0x00: data pointer (int*)
//   +0x04: element count (int)
//   +0x08: capacity (int, number of elements allocated)
void __thiscall DynamicArray8::reserve(uint newCapacity) {
    int* oldData;
    int* newData;
    uint i;

    if ((uint)this->capacity < newCapacity) {
        // Allocate new buffer: newCapacity * 8 bytes (two 4-byte fields per element)
        newData = (int*)FUN_009c8e80(newCapacity * 8);
        if (this->data != NULL) {
            i = 0;
            if (this->count != 0) {
                do {
                    if (newData != NULL) {
                        oldData = this->data;
                        newData[i * 2] = oldData[i * 2];
                        newData[i * 2 + 1] = oldData[i * 2 + 1];
                    }
                    i++;
                } while (i < (uint)this->count);
            }
            FUN_009c8f10(this->data);
        }
        this->data = newData;
        this->capacity = newCapacity;
    }
}