// FUNC_NAME: Array::reserve
void __thiscall Array::reserve(int *this, uint newCapacity)
{
    uint oldCapacity = this[2]; // +0x08: capacity
    if (oldCapacity < newCapacity) {
        undefined4 *newData = (undefined4 *)FUN_009c8e80(newCapacity * 4); // allocate new buffer
        if (this[0] != 0) { // +0x00: data pointer
            uint i = 0;
            undefined4 *dst = newData;
            if (this[1] != 0) { // +0x04: count
                do {
                    if (dst != (undefined4 *)0x0) {
                        *dst = *(undefined4 *)(this[0] + i * 4); // copy element
                    }
                    i = i + 1;
                    dst = dst + 1;
                } while (i < (uint)this[1]);
            }
            FUN_009c8f10(this[0]); // free old buffer
        }
        this[0] = (int)newData; // update data pointer
        this[2] = newCapacity;  // update capacity
    }
    return;
}