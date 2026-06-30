// FUNC_NAME: Deallocator::deallocateObject
// Address: 0x00651c20
// This function performs object cleanup and deallocation. It calls the internal
// cleanup routine (likely virtual destructor or release method) and then frees
// the memory if the pointer is non-null.
void __cdecl Deallocator::deallocateObject(void* ptr)
{
    // Call the cleanup function (e.g., destructor, release resources)
    FUN_00652100();

    // If the pointer is valid, free the memory
    if (ptr != 0) {
        FUN_009c8eb0(ptr); // likely operator delete or free
    }
}