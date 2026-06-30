// FUNC_NAME: shutdownAndDelete
// Address: 0x006524b0
// Identified role: Cleanup routine that calls a common deinit function and optionally deletes an object.
// Likely used in destructor patterns or manual cleanup.

void __cdecl shutdownAndDelete(void *object)
{
    // Call common shutdown/deinitialization routine (likely static or global)
    FUN_00652640();

    // If the object pointer is non-null, deallocate it
    if (object != (void *)0x0) {
        FUN_009c8eb0(object); // operator delete or custom deallocator
    }

    return;
}