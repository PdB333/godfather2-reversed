// FUN_00442a30: MainSystem::shutdown

void __thiscall MainSystem::shutdown(MainSystem *this)
{
    // +0x7C: pointer to manager1 vtable
    // +0x6C: object managed by manager1 (primary)
    // +0x78: optional secondary object managed by manager1 (or null)
    // Same pattern repeated at offsets:
    // +0x68, +0x58, +0x64 for manager2
    // +0x50, +0x40, +0x4C for manager3
    // +0x3C, +0x2C, +0x38 for manager4
    // +0x18: standalone object pointer (released via dedicated function)

    // Set initial vtable pointers (these might be intermediate or derived class vtables)
    *(int **)this = &PTR_FUN_00e31160;        // +0x00: vtable for this class
    *(int **)((char *)this + 4) = &PTR_LAB_00e31164;  // +0x04: unknown pointer
    *(int **)((char *)this + 12) = &PTR_LAB_00e31170;  // +0x0C: unknown

    // Clean up global data structures
    FUN_004086d0(&DAT_01206970);   // probably reset global state 1
    FUN_004086d0(&DAT_012069d4);   // global state 2

    // Release manager1's objects
    {
        void **manager1Vtable = (void **)this->ptrs[0x1f];  // +0x7C
        void **releaseFunc = (void **)(*((int *)manager1Vtable[4])); // vtable[4] is release function
        void *obj1 = this->ptrs[0x1b];  // +0x6C
        ((void (*)(void *))releaseFunc)(obj1); // release primary object

        if (this->ptrs[0x1e] != NULL) // +0x78
        {
            ((void (*)(void *))releaseFunc)(this->ptrs[0x1e]); // release secondary object
        }

        void **finalizeFunc = (void **)(*((int *)manager1Vtable[12])); // vtable[12] is finalize/sub-shutdown
        ((void (*)(void))finalizeFunc)(); // finalize manager itself
    }

    // Release manager2's objects
    {
        void **manager2Vtable = (void **)this->ptrs[0x1a];  // +0x68
        void **releaseFunc = (void **)(*((int *)manager2Vtable[4]));
        void *obj2 = this->ptrs[0x16];  // +0x58
        ((void (*)(void *))releaseFunc)(obj2);

        if (this->ptrs[0x19] != NULL) // +0x64
        {
            ((void (*)(void *))releaseFunc)(this->ptrs[0x19]);
        }

        void **finalizeFunc = (void **)(*((int *)manager2Vtable[12]));
        ((void (*)(void))finalizeFunc)();
    }

    // Release manager3's objects
    {
        void **manager3Vtable = (void **)this->ptrs[0x14];  // +0x50
        void **releaseFunc = (void **)(*((int *)manager3Vtable[4]));
        void *obj3 = this->ptrs[0x10];  // +0x40
        ((void (*)(void *))releaseFunc)(obj3);

        if (this->ptrs[0x13] != NULL) // +0x4C
        {
            ((void (*)(void *))releaseFunc)(this->ptrs[0x13]);
        }

        void **finalizeFunc = (void **)(*((int *)manager3Vtable[12]));
        ((void (*)(void))finalizeFunc)();
    }

    // Release manager4's objects
    {
        void **manager4Vtable = (void **)this->ptrs[0xf];  // +0x3C
        void **releaseFunc = (void **)(*((int *)manager4Vtable[4]));
        void *obj4 = this->ptrs[0xb];  // +0x2C
        ((void (*)(void *))releaseFunc)(obj4);

        if (this->ptrs[0xe] != NULL) // +0x38
        {
            ((void (*)(void *))releaseFunc)(this->ptrs[0xe]);
        }

        void **finalizeFunc = (void **)(*((int *)manager4Vtable[12]));
        ((void (*)(void))finalizeFunc)();
    }

    // Release standalone object (if any) via its own cleanup function
    if (this->ptrs[6] != NULL) // +0x18
    {
        FUN_009c8f10(this->ptrs[6]); // custom destructor/release
    }

    // Additional global cleanup
    FUN_004083d0(); // reset some engine global
    FUN_0049c640(); // finalize audio/input?

    // Restore original vtable (likely base class or neutral state)
    *(int **)this = &PTR_LAB_00e31180;

    // Signal that the system is shut down
    DAT_0122342c = 0;  // global shutdown flag
}