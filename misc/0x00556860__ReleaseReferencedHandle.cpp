// FUNC_NAME: ReleaseReferencedHandle
void __fastcall ReleaseReferencedHandle(void* obj)
{
    // obj+0x40 holds a pointer to a reference-counted object
    void** handlePtr = *(void***)((char*)obj + 0x40);
    if (handlePtr != nullptr)
    {
        // Call helper to potentially decrement reference or perform cleanup
        FUN_00557020(); // Possibly decrements outer reference or resets state

        // Check reference count at offset 4 and 6 (16-bit values)
        short* refCount = (short*)(handlePtr + 1); // offset +4 from handlePtr
        if (*refCount != 0)
        {
            // Decrement count at offset 6
            short* count2 = (short*)((char*)handlePtr + 6);
            *count2 = *count2 - 1;
            if (*count2 == 0)
            {
                // If second count reaches zero, call function pointer from handlePtr[0] with argument 1
                void (*releaseFunc)(int) = (void (*)(int))(*handlePtr);
                releaseFunc(1);
            }
        }
        // Clear the handle pointer
        *(void***)((char*)obj + 0x40) = nullptr;
    }
}