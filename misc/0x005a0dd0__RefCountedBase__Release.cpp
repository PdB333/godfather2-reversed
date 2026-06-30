// FUNC_NAME: RefCountedBase::Release
void __fastcall RefCountedBase::Release(int* thisPtr) {
    int* refCountPtr = (int*)*thisPtr; // Dereference to get pointer to ref count (shared ref count structure)
    
    if (refCountPtr != nullptr) {
        (*refCountPtr)--; // Decrement reference count
        if (*refCountPtr == 0) {
            // Call cleanup/destructor for the managed object
            FUN_005a1b40();
            // Free the reference count block (size 0x30) using the global deallocation function
            ((void (__fastcall*)(void*, int))DAT_0119caf8)(refCountPtr, 0x30);
        }
    }
}