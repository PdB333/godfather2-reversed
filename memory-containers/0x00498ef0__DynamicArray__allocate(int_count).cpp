// FUNC_NAME: DynamicArray::allocate(int count)
int __thiscall DynamicArray::allocate(int count)
{
    // Call base class initialization (e.g., zero out vtable or other members)
    initializeBase(); // FUN_00498f80

    // Compute size in bytes for array of (count+1) 32-bit elements.
    // Use 64-bit multiplication to detect overflow.
    long long size64 = (long long)(count + 1) * 4;
    // If multiplication overflowed (high 32 bits non‑zero), force size to 0xFFFFFFFF,
    // otherwise use the low 32 bits as the allocation size.
    unsigned int size = (int)(size64 >> 32) != 0 ? 0xFFFFFFFF : (unsigned int)size64;

    // Allocate memory and store pointer at offset 0x30 (array data pointer)
    this->arrayData = (int*)allocateMemory(size); // FUN_009c8e80
    return this;
}