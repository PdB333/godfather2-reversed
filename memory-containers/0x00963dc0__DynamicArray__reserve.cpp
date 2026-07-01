// FUNC_NAME: DynamicArray::reserve
// Address: 0x00963dc0
// This function ensures the dynamic array has at least 'newCapacity' slots.
// Struct layout: data (+0x00), count (+0x04), capacity (+0x08)
void __thiscall DynamicArray::reserve(int* this, uint newCapacity)
{
    int oldData;
    int newData;
    uint i;
    
    if ((uint)this[2] < newCapacity) {
        // Allocate new block of newCapacity * 4 bytes
        newData = (int)FUN_009c8e80(newCapacity * 4);
        if (this[0] != 0) {
            i = 0;
            // Copy existing elements up to current count
            if (this[1] != 0) {
                do {
                    // Decompiler artifact: the null check on destination is always true
                    if ((int*)newData != (int*)0x0) {
                        *(uint*)(newData + i * 4) = *(uint*)(this[0] + i * 4);
                    }
                    i = i + 1;
                } while (i < (uint)this[1]);
            }
            // Free old data block
            FUN_009c8f10(this[0]);
        }
        this[0] = newData;
        this[2] = newCapacity; // Update capacity
    }
    return;
}