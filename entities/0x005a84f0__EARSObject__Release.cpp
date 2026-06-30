// FUNC_NAME: EARSObject::Release
void EARSObject::Release()
{
    // Call the base destructor or cleanup logic
    destructor();

    // Check if the reference count (stored at offset +2) is zero
    if (*(short *)(this + 2) == 0)
    {
        // Get the actual memory allocation pointer (may differ from 'this')
        void *memoryPointer = getAllocation();

        // Free the memory using the global deallocator with size 8
        gDeallocator(memoryPointer, 8);
    }
}