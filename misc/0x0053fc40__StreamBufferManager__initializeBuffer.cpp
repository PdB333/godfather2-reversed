// FUNC_NAME: StreamBufferManager::initializeBuffer
void __thiscall StreamBufferManager::initializeBuffer(void)
{
    // Allocate aligned memory for a control structure (size 0x330, alignment 16)
    int *controlBlock = (int *)_aligned_malloc(0x330, 0x10);
    if (controlBlock != nullptr) {
        // Create a new object from the reference counted object at this+0x1c
        // FUN_00aa23a0 likely constructs/allocates something from a resource manager
        this->bufferHandle = FUN_00aa23a0(this->resourceManager, 0x10);
    }
    else {
        this->bufferHandle = 0;
    }

    // Register this buffer handle with the resource manager (e.g., bind to a stream)
    // DAT_0053fc30 is likely a vtable or callback structure (e.g., stream callbacks)
    FUN_00c6eb30(this->resourceManager, this->bufferHandle, &DAT_0053fc30, 0);

    // Decrement reference count on the resource manager (smart pointer pattern)
    // Offsets: resourceManager +0x4 is the ref count; if zero, call release via vtable
    int *refCount = (int *)(this->resourceManager->refCount);
    *refCount -= 1;
    if (*refCount == 0) {
        // Call vtable[0] (destructor/release) with argument 1 (likely delete)
        this->resourceManager->vtable->release(1);
    }

    // Get current thread's TLS slot (unused, likely for debug or context)
    TlsGetValue(DAT_01139810);

    // Allocate a large buffer for streaming (0x80000 bytes, flag 1 = aligned/pool)
    this->streamBuffer = (void *)FUN_00aa28b0(0x80000, 1);

    // Call the third virtual function (offset 8) on the bufferHandle object,
    // passing the allocated buffer and size (initialize ring buffer?)
    // bufferHandle is a pointer to an object with a vtable; offset 8 is the 3rd function
    (this->bufferHandle->vtable->setBuffer)(this->streamBuffer, 0x80000);
}