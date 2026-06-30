// FUNC_NAME: ReferenceCounted::Release
void ReferenceCounted::Release()
{
    // Call base class destructor or cleanup
    this->cleanup();

    // If reference count (short at offset +0x2) is zero, deallocate
    if (*(short *)(this + 2) == 0)
    {
        // Get global allocator/manager
        void *allocator = getMemoryAllocator();
        // Call global delete function with allocator and size 8 (size of this object)
        gDeleteFunc(allocator, 8);
    }
}