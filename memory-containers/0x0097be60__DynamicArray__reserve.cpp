// FUNC_NAME: DynamicArray::reserve
// Address: 0x0097be60
// Role: Resize/grow the internal buffer of a dynamic array (int-based) to at least newCapacity.
// Structure offsets: data = this[0], count = this[1], capacity = this[2]

void __thiscall DynamicArray::reserve(int* this, uint newCapacity)
{
    int* newData;
    uint i;
    int* src;

    if ((uint)this[2] < newCapacity) {
        // Allocate new buffer (4 bytes per element)
        newData = (int*)allocateMemory(newCapacity * 4);
        if (this[0] != 0) {
            i = 0;
            src = newData;
            if (this[1] != 0) {
                do {
                    if (src != (int*)0x0) {
                        *src = *(int*)(this[0] + i * 4);
                    }
                    i = i + 1;
                    src = src + 1;
                } while (i < (uint)this[1]);
            }
            freeMemory(this[0]);
        }
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}