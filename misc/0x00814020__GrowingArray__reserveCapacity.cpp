// FUNC_NAME: GrowingArray::reserveCapacity
// Function address: 0x00814020
// Role: Ensures the internal buffer has at least the requested capacity.
// Reallocates if necessary, copying existing elements (each 8 bytes: 4-byte int + two 2-byte shorts).
// Field offsets: this+0x00 = data pointer, this+0x04 = count, this+0x08 = capacity

void __thiscall GrowingArray::reserveCapacity(uint minimumCapacity)
{
    int *this = thisptr; // actually 'this' in __thiscall is ecx, but for clarity
    if (this[2] < minimumCapacity) {
        // Allocate new block: each element is 8 bytes
        undefined4 *newData = (undefined4 *)allocateMemory(minimumCapacity * 8);
        if (this[0] != 0) {
            if (this[1] != 0) {
                uint i = 0;
                undefined4 *src = (undefined4 *)this[0];
                undefined4 *dst = newData;
                do {
                    // Copy element (8 bytes)
                    *dst = *src;
                    *(undefined2 *)(dst + 1) = *(undefined2 *)(src + 1);
                    *(undefined2 *)((int)dst + 6) = *(undefined2 *)((int)src + 6);
                    i++;
                    src += 2; // each element is 2 * undefined4 (8 bytes)
                    dst += 2;
                } while (i < this[1]);
            }
            freeMemory((void *)this[0]);
        }
        this[0] = (int)newData; // update data pointer
        this[2] = minimumCapacity; // update capacity
    }
}