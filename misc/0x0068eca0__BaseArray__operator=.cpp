// FUNC_NAME: BaseArray::operator=
int* __thiscall BaseArray::operator=(int* this, int* other) {
    int elementSize;
    undefined4* destPtr;
    uint idx;

    if (this != other) {
        // If current capacity is less than other's size, need to reallocate
        if ((uint)this[2] < (uint)other[1]) {
            FUN_009c8f10(*this);  // freeOldBuffer
            int newCapacity = other[1];
            this[2] = newCapacity;
            if (newCapacity == 0) {
                elementSize = 0;
            }
            else {
                elementSize = FUN_009c8e80(newCapacity * 4);  // allocateBuffer
            }
            *this = elementSize;  // Set new buffer pointer
        }

        idx = 0;
        if (other[1] != 0) {
            do {
                destPtr = (undefined4*)(*this + idx * 4);
                if (destPtr != (undefined4*)0x0) {
                    *destPtr = *(undefined4*)(idx * 4 + *other);
                }
                idx = idx + 1;
            } while (idx < (uint)other[1]);
        }
        this[1] = other[1];  // Copy size
    }
    return this;
}