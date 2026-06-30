// FUN_00473840: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(void *this, int param2)
{
    // Call base class constructor or initializer with given parameter
    FUN_0046c590(param2); // likely baseObjectInit(param2)

    // Set vtable pointers – multiple inheritance or interface vtable slots
    *(void **)this = &PTR_FUN_00e32af4;                    // primary vtable (offset +0x00)
    *(void **)((char *)this + 0x3C) = &PTR_LAB_00e32b18;   // secondary vtable (offset +0x3C)
    *(void **)((char *)this + 0x48) = &PTR_LAB_00e32b28;   // tertiary vtable (offset +0x48)
    *(void **)((char *)this + 0x50) = &PTR_LAB_00e32b2c;   // quaternary vtable (offset +0x50)
                                                         // note: first assignment to +0x50 is overwritten – likely a decompilation artifact

    // Initialize two byte flags
    *((char *)this + 0x54) = 0; // +0x54: unknownFlag1
    *((char *)this + 0x55) = 0; // +0x55: unknownFlag2
}