// FUNC_NAME: ObjectArray::createArray
undefined4 * __thiscall ObjectArray::createArray(int *this, int count, int *allocator, undefined4 param4) {
    undefined4 defaultObject;
    undefined4 *arrayPtr;

    this[1] = 0;              // +0x04: some field (initialized to 0)
    this[2] = count;          // +0x08: store element count
    defaultObject = FUN_004265d0(param4, allocator);  // +0x0C: get default object/initializer
    this[3] = defaultObject;  // +0x0C: store default
    this[4] = allocator;      // +0x10: store allocator pointer
    // Call virtual method at vtable offset 8 on allocator object (pre-initialization?)
    (*(void (**)(void))(*allocator + 8))();

    arrayPtr = (undefined4 *)this[3];  // use defaultObject if not null
    if (arrayPtr == (undefined4 *)0x0) {
        arrayPtr = &DAT_01218a14;      // fallback global default
    }
    // Call first virtual method (offset 0) on allocator: allocate memory block
    // size = count * 0x130 (304 bytes per element)
    *this = (*(void *(*)(int, void *))(** (void ***)this[4]))(count * 0x130, (void *)arrayPtr);
    return this;
}