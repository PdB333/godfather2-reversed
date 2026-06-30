// FUNC_NAME: DynamicArray::reserve
// Function address: 0x006ba910
// Role: Ensures the dynamic array has at least the specified capacity by reallocating if necessary.
// Structure: +0x00 = array pointer (int*), +0x04 = size (uint), +0x08 = capacity (uint)
// Element size: 8 bytes (pair of int32 or int64?)

void __thiscall DynamicArray::reserve(int *this, uint capacity)
{
    undefined4 *newBuffer;
    undefined4 *src;
    uint i;
    undefined4 *dst;

    if ((uint)this[2] < capacity) {
        // Allocate new buffer with 8 bytes per element
        newBuffer = (undefined4 *)FUN_009c8e80(capacity * 8);
        if (this[0] != 0) {
            // Copy existing elements
            i = 0;
            dst = newBuffer;
            if (this[1] != 0) {
                do {
                    src = (undefined4 *)(this[0] + i * 8);
                    if (dst != (undefined4 *)0x0) {
                        *dst = *src;
                        dst[1] = src[1];
                    }
                    i = i + 1;
                    dst = dst + 2;
                } while (i < (uint)this[1]);
            }
            // Free old buffer
            FUN_009c8f10(this[0]);
        }
        // Update buffer and capacity
        this[0] = (int)newBuffer;
        this[2] = capacity;
    }
}