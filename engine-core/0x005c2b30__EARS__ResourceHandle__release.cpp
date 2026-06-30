// FUNC_NAME: EARS::ResourceHandle::release

void __fastcall EARS::ResourceHandle::release(int* thisPtr)
{
    // Clear helper fields
    thisPtr[2] = 0; // +0x08 (e.g., weak reference count)
    thisPtr[1] = 0; // +0x04 (e.g., strong reference count)

    // Release the owned object if present
    if (thisPtr[0] != 0) {
        // Virtual deallocation via global manager at DAT_012234ec
        // The manager's vtable at offset 4 has a release function at index 1
        void** vtable = *(void***)(DAT_012234ec + 4);
        void (*releaseFunc)(void*, int) = (void (*)(void*, int))vtable[1];
        releaseFunc((void*)thisPtr[0], 0); // second param 0 = immediate release
    }

    // Null out the pointer
    thisPtr[0] = 0; // +0x00 (owned object pointer)
}