// FUNC_NAME: EARSBaseObject::release
void EARSBaseObject::release()
{
    // param_1 is the this pointer (int*)
    int* thisPtr = param_1;

    // Check if the object's reference count or alive flag is non-zero
    if (*thisPtr != 0) {
        // If there is a cleanup callback at offset +0x24 (index 9 in int array), call it
        void (*cleanupFunc)() = (void (*)())(thisPtr[9]); // +0x24
        if (cleanupFunc != 0) {
            cleanupFunc();
        }

        // Call the underlying release/deallocation routine
        FUN_004dd960(); // Possibly EARSHeap::free or reference decrement
    }
}