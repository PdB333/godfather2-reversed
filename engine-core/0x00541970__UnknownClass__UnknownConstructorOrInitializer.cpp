// FUNC_NAME: UnknownClass::UnknownConstructorOrInitializer
// Address: 0x00541970
// This function appears to be a member function that initializes the object and may optionally call the destructor based on a flag.
// The call to the vtable entry at offset 4 (likely the scalar deleting destructor) is invoked with a 0 argument (meaning only destruct, no free) when param_2 bit 0 is set.
// Global at DAT_01223410 is likely a game singleton (e.g., theGame). Offset 0x2d4 leads to a vtable pointer.

__thiscall int UnknownClass::constructorOrInit(int this_arg, byte param_2)
{
    // Call a member function (likely a common initializer)
    this->initialize(); // FUN_005419a0, called with this (implicit ecx)

    if ((param_2 & 1) != 0)
    {
        // Call virtual destructor (scalar deleting destructor with flag=0) via vtable
        // DEREF(DEREF(DAT_01223410 + 0x2d4) + 4) is a function pointer (void __thiscall)(void*, int)
        typedef void (__thiscall *DestructorFunc)(void* self, int flag);
        DestructorFunc destructor = *(DestructorFunc*)(*(int*)(DAT_01223410 + 0x2d4) + 4);
        destructor(this_arg, 0);
    }

    return this_arg;
}