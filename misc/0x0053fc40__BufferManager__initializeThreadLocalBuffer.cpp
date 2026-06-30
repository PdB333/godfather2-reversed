// FUNC_NAME: BufferManager::initializeThreadLocalBuffer
void BufferManager::initializeThreadLocalBuffer()
{
    // Allocate aligned memory for a buffer manager object (0x330 bytes, 16-byte alignment)
    int* alignedMem = (int*)__aligned_malloc(0x330, 0x10);
    undefined4 newObj;
    if (alignedMem == 0) {
        newObj = 0;
    }
    else {
        // Construct/new object at the memory pointed by this+0x1c (shared pointer target?)
        // The second argument 0x10 might be a size or alignment hint
        newObj = FUN_00aa23a0(*(undefined4*)(this + 0x1c), 0x10);
    }
    *(undefined4*)(this + 0x10) = newObj;

    // Decrement reference count on the shared resource at this+0x1c
    FUN_00c6eb30(*(undefined4*)(this + 0x1c), newObj, &DAT_0053fc30, 0);

    // Release the shared pointer: decrement ref count, delete if zero
    undefined4** sharedPtr = *(undefined4***)(this + 0x1c);
    int* refCount = sharedPtr + 4;
    *refCount = *refCount - 1;
    if (*refCount == 0) {
        (*(code**)*sharedPtr)(1); // call destructor via vtable at offset 0? Actually offset 0 is likely destructor
    }

    // Retrieve thread-local storage (TLS) value (possibly a per-thread allocator)
    TlsGetValue(DAT_01139810);

    // Allocate a large buffer (0x80000 = 512KB, second parameter 1 might be alignment or flags)
    undefined4 largeBuffer = FUN_00aa28b0(0x80000, 1);
    *(undefined4*)(this + 0x14) = largeBuffer;

    // Call virtual method at offset 8 on the object at this+0x10 (likely a "setBuffer" or "assign")
    // with the large buffer and size
    (**(code**)(**(int**)(this + 0x10) + 8))(largeBuffer, 0x80000);
}