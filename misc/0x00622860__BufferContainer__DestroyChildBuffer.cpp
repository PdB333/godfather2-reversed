// FUNC_NAME: BufferContainer::DestroyChildBuffer
void BufferContainer::DestroyChildBuffer()
{
    // Temporary buffer for cleanup notification (12 bytes)
    char notificationBuf[12];

    // Notify about child cleanup with various parameters
    // Third argument: value stored at child pointer (dereferenced twice)
    // Fifth argument: child pointer itself
    NotifyChildCleanup(notificationBuf, this, **(void**)(this + 0x1c), this, *(void**)(this + 0x1c));

    // Call virtual deallocator function from vtable at this+4
    // vtable entry 1 (offset +4) takes a pointer and size (0x18 = 24 bytes)
    // This is likely a custom memory deallocation hook
    typedef void (*DeallocFunc)(void*, unsigned int);
    DeallocFunc dealloc = *(DeallocFunc*)(*(int*)(this + 4) + 4);
    dealloc(*(void**)(this + 0x1c), 0x18);

    // Clear child pointer and associated size/count field
    *(void**)(this + 0x1c) = nullptr; // +0x1c: pointer to allocated 24-byte child object
    *(int*)(this + 0x20) = 0;         // +0x20: size or count field (reset)
}