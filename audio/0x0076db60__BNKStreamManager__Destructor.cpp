// FUNC_NAME: BNKStreamManager::Destructor
void __fastcall BNKStreamManager::Destructor(BNKStreamManager* this) // param_1 = this
{
    // +0x00: vtable pointer, set to base class vtable (0x00d662c0) at entry
    *(int**)this = (int*)0x00d662c0;

    // Release allocated resources of sizes 0x17 and 0x14 (likely sub-objects)
    deallocateMemory(0x17);
    deallocateMemory(0x14);

    // Bit field at +0x74: byte flags
    unsigned char flags = *(unsigned char*)((int)this + 0x74);
    if (flags & 2)
    {
        // Release member at +0x5C (pointer to a stream or similar)
        releasePointer(*(void**)((int)this + 0x5C), 0);
        *(unsigned char*)((int)this + 0x74) &= 0xFD; // clear bit 1
    }

    // Check if both bit0 and bit2 are clear, and the member at +0x5C is non-null
    if ((flags & 5) == 0 && *(void**)((int)this + 0x5C) != 0)
    {
        // Obtain a global singleton via DAT_01131018
        int* singleton = getSingleton(DAT_01131018);
        if (singleton != 0)
        {
            // Call virtual function at index 0x38 (0x38 bytes? index 14)
            bool (*isReady)(void) = (bool (*)())(*(int*)(*singleton + 0x38));
            if (isReady())
            {
                *(unsigned char*)((int)this + 0x74) |= 1; // set bit 0
                updateNotification();
            }
        }
    }

    // Global pre-cleanup call
    globalPreCleanup();

    // Member at +0x78: pointer to a timer or callback object
    int* timerPtr = *(int**)((int)this + 0x78);
    if (timerPtr != 0)
    {
        *(int*)(timerPtr + 8) = 0; // clear some field
        *(int*)((int)this + 0x78) = 0; // nullify member
    }

    // Set vtable to derived class? Actually final vtable for base (0x00d63090)
    *(int**)this = (int*)0x00d63090;

    // Destroy sub-object at +0x1A (offset 0x68) – likely a pointer to another object
    if (*(int*)((int)this + 0x68) != 0)
    {
        destroySubObject((int*)((int)this + 0x68));
    }

    // Global post-cleanup call
    globalPostCleanup();
}