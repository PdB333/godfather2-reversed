// FUNC_NAME: SomeClass::SomeClass
void __thiscall SomeClass::SomeClass(SomeClass* this, int arg1, int arg2, __int64 arg3, int arg4, __int64 arg5, int arg6, __int64 arg7, int arg8, int arg9)
{
    // 'this' points to an object; the first field is a pointer to a vtable descriptor block.
    void* pDescriptor = *(void**)this; // get pointer at offset 0

    // Write the address of a vtable function table at offset 0x14 in the descriptor.
    *(void**)((char*)pDescriptor + 0x14) = (void*)&PTR_FUN_01124640;

    // Increment the stored vtable pointer by 4 (advancing to next vtable entry?).
    int* pEntry = (int*)((char*)pDescriptor + 0x14);
    *pEntry = *pEntry + 4;

    // Call the base class constructor with all forwarded arguments.
    FUN_004b90d0(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}