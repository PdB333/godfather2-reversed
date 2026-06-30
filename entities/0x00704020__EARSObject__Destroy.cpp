// FUNC_NAME: EARSObject::Destroy
int* __thiscall EARSObject::Destroy(int* this, byte deallocateFlag)
{
    // If internal pointer at offset 0x00 is non-null, run the full destructor chain
    if (this[0] != 0) {
        FUN_004daf90(this); // likely calls destructors of base class and members
    }
    // If the least significant bit of deallocateFlag is set, free the memory
    if (deallocateFlag & 1) {
        FUN_009c8eb0(this); // operator delete or custom deallocation
    }
    return this;
}