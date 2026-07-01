// FUNC_NAME: Array8::constructor
undefined4* __thiscall Array8::constructor(undefined4* this, uint count)
{
    void* data;
    // Allocate memory for 'count' elements of size 8, with overflow detection
    // The expression: -(uint)((int)((ulonglong)count * 8 >> 0x20) != 0) | (uint)((ulonglong)count * 8)
    // If the high 32 bits of the 64-bit product are non-zero, the result is all-ones (overflow sentinel)
    data = (void*)FUN_009c8e50(-(uint)((int)((ulonglong)count * 8 >> 0x20) != 0) | (uint)((ulonglong)count * 8));
    if (data == nullptr) {
        data = nullptr;
    }
    else {
        // Call element constructor (LAB_0084e3d0) for each of the 'count' elements (each 8 bytes)
        _vector_constructor_iterator_(data, 8, count, (_func_void_ptr_void_ptr*)&LAB_0084e3d0);
    }
    this[0] = data;          // +0x00: pointer to allocated data
    this[1] = count;         // +0x04: number of elements
    this[2] = 0;             // +0x08: capacity (initially 0, likely resized later)
    this[3] = 0;             // +0x0C: unknown (maybe flags or iterator)
    return this;
}