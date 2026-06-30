// FUNC_NAME: EARSBase::EARSBase
// Address: 0x00680bd0
// This is a constructor for a base EARS object. It sets the vtable at offset +0x20, 
// clears a global construction flag, performs base initialization, and optionally 
// calls a cleanup function if the second bit (0x02) of the flags parameter is set.

// +0x00: 20 bytes of base class data (assumed from vtable offset)
// +0x20: vtable pointer
int __thiscall EARSBase::EARSBase(byte flags)
{
    // Set vtable pointer at offset 0x20 from object start
    this->vtable = &PTR_LAB_00d580c8; // vtable for EARSBase

    // Reset global flag (possibly g_objectCount or g_constructing)
    DAT_011298b4 = 0;

    // Call the common base initialization routine
    FUN_007edfb0(); // likely baseInitialize()

    // If the low bit of flags is set, call a cleanup function
    // (possibly a "delete" or "release" for error handling)
    if ((flags & 1) != 0)
    {
        FUN_009c8eb0(this); // cleanup(this)
    }

    return this;
}