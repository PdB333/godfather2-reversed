// FUNC_NAME: SomeClass::SomeClass

// Function at 0x006d71e0 - Constructor for an object that may dynamically allocate a sub-block of 0x270 bytes.
// param_1: this pointer (returned)
// param_2: flags; bit0 indicates whether to allocate additional memory (size 0x270) via a vtable-based allocator.
int __thiscall SomeClass::SomeClass(void *this, byte flags)
{
    // Call base class constructor (likely in the same inheritance chain)
    // FUN_006d6500 - base constructor, assumed to be __thiscall on 'this'
    BaseClass::baseCtor(this);

    if (flags & 1)
    {
        // Get a pointer to the allocator vtable for this class (global)
        // FUN_009c8f80 returns a pointer to an int (the vtable pointer)
        int *pAllocVtable = (int *)getClassAllocatorVtable();
        // Dereference to get the vtable address, then take function at offset 4 (index 1)
        // This function is likely "allocate" or "construct" for a sub-object
        void (__thiscall *allocFunc)(void *, int) = (void (__thiscall *)(void *, int))(*pAllocVtable + 4);
        // Call the allocator with 'this' and size 0x270
        allocFunc(this, 0x270);
    }
    return (int)this;
}