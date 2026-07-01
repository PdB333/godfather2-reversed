// FUNC_NAME: constructWithDestroyFlag
// Function address: 0x008ca960
// Role: Constructor-like initialization that sets vtable and optionally calls a cleanup/destructor function based on a flag bit.

void* __thiscall constructWithDestroyFlag(void* object, byte flag)
{
    // Set vtable pointer to the class-specific vtable (address 0x00d7c0c8)
    *(void**)object = (void*)0x00d7c0c8; // +0x00: vtable

    // Call base class initialization (likely a base constructor or initializer)
    FUN_004149b0();

    // If the lowest bit of flag is set, call deallocation/cleanup function
    if ((flag & 1) != 0)
    {
        FUN_009c8eb0(object); // Likely a destructor or memory deallocator
    }

    return object;
}