// FUNC_NAME: DynamicArray::reserveCapacity
// Address: 0x00917930
// Role: Ensures the internal buffer has at least `requestedCapacity` slots.
//        If current capacity is insufficient, allocates a new buffer, copies existing elements,
//        frees the old buffer, and updates the capacity.
// Note: param_1 is 'this' pointer to a struct with fields:
//   +0x00: data pointer (int*)
//   +0x04: current size (uint) - number of elements stored
//   +0x08: capacity (uint) - number of slots allocated

void __thiscall DynamicArray::reserveCapacity(int *this, uint requestedCapacity)
{
    undefined4 *newBuffer;
    uint i;
    undefined4 *dest;

    if ((uint)this[2] < requestedCapacity) {
        newBuffer = (undefined4 *)FUN_009c8e80(requestedCapacity * 4); // allocate memory
        if (*this != 0) {
            i = 0;
            dest = newBuffer;
            if (this[1] != 0) {
                do {
                    if (dest != (undefined4 *)0x0) {
                        *dest = *(undefined4 *)(*this + i * 4);
                    }
                    i = i + 1;
                    dest = dest + 1;
                } while (i < (uint)this[1]);
            }
            FUN_009c8f10(*this); // free old buffer
        }
        *this = (int)newBuffer;
        this[2] = requestedCapacity;
    }
    return;
}