// FUNC_NAME: EARSArray::reserve
// Function address: 0x008be0b0
// Purpose: Resize an EA EARS dynamic array to a new capacity if it's larger than current.
// The array structure (this) is assumed to be [data_ptr, element_count, capacity].
// Note: param_2 is the desired new capacity.

void __thiscall EARSArray::reserve(int* this, uint newCapacity)
{
    undefined4* newData;
    uint i;
    undefined4* dest;

    // Only grow if new capacity exceeds current capacity
    if ((uint)this[2] < newCapacity) {
        // Allocate new memory block (size = newCapacity * 4 bytes)
        newData = (undefined4*)FUN_009c8e80(newCapacity * 4);

        // Copy existing elements if any exist
        if (*this != 0) {
            i = 0;
            dest = newData;
            if (this[1] != 0) {
                do {
                    if (dest != (undefined4*)0x0) {
                        *dest = *(undefined4*)(*this + i * 4);
                    }
                    i = i + 1;
                    dest = dest + 1;
                } while (i < (uint)this[1]);
            }
            // Free old data
            FUN_009c8f10(*this);
        }

        // Update array structure: new data pointer and capacity
        *this = (int)newData;
        this[2] = newCapacity;
    }
    return;
}