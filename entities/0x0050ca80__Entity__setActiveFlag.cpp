// FUNC_NAME: Entity::setActiveFlag
void Entity::setActiveFlag(int param_1) // param_1 is likely an index or sub-offset? actually this pointer is param_1?
{
    // Call to unknown function with in_EAX (likely a register parameter) and this pointer
    FUN_0050c9a0(in_EAX, this);

    // Access thread-local storage array at FS:0x2c (TLS table pointer)
    // Dereference to get TLS base, then offset 8 to get per-thread structure
    // ESI * 0x50 + 0x54 gives an offset into that structure, then + *this (offset from this pointer)
    byte* flagByte = (byte*)(*(int*)(**(int**)(__readfsdword(0x2c) + 8) + unaff_ESI * 0x50 + 0x54 + *this));
    
    // Set bit 0 of that byte
    *flagByte = *flagByte | 1;

    // Call another unknown function
    FUN_0050fdc0(this);
}