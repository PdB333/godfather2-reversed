// FUNC_NAME: EARSObject::EARSObject

undefined4 __thiscall EARSObject::EARSObject(EARSObject* this, byte flags)
{
    // Call base class or common initialization
    baseConstructor();  // FUN_00478520

    // If the lowest bit of flags is set, call a virtual initialization method
    if ((flags & 1) != 0)
    {
        // Retrieve vtable pointer from global engine state at offset 0x2d4
        // This is likely a structure field such as g_pEngine->m_pVTable
        int* vtable = *(int**)(DAT_01223410 + 0x2d4);  // +0x2d4
        // The second entry in the vtable (offset +4) points to an init function
        // Call it with this pointer and argument 0
        typedef void (__thiscall *InitFunc)(void*, int);
        ((InitFunc)(vtable[1]))(this, 0);
    }

    return this;
}