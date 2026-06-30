// FUNC_NAME: SomeClass::~SomeClass
void __thiscall SomeClass::~SomeClass(SomeClass* this) {
    // Set vtable to destructor vtable (offset 0x00)
    this->vtable = (SomeClassVTable*)&PTR_FUN_00e3a9e0;
    // Set another vtable (offset 0x04)
    *(int*)((char*)this + 4) = (int)&PTR_LAB_00e3aa78;

    // Check if subobject at +0x34 (offset 0x0d) exists
    if (*(int*)((char*)this + 0x34) != 0) {
        // Call its virtual function at index 2 (vtbl+8)
        (**(void(__thiscall**)(void*))(**(int**)((char*)this + 0x34) + 8))((void*)*(int*)((char*)this + 0x34));
    }
    // Nullify subobject pointer (offset 0x34)
    *(int*)((char*)this + 0x34) = 0;

    // Check if another subobject at +0x350 (offset 0xd4) exists
    if (*(int*)((char*)this + 0x350) != 0) {
        // Call function pointer stored at +0x35c (offset 0xd7)
        (*(void(__cdecl*)(int))*(int*)((char*)this + 0x35c))(*(int*)((char*)this + 0x350));
    }

    // Set vtable for subobject at +0x34c (offset 0xd3) to purecall
    *(int*)((char*)this + 0x34c) = (int)&PTR___purecall_00e3a9d0;
    // Set another vtable at +0x38 (offset 0x0e)
    *(int*)((char*)this + 0x38) = (int)&PTR_FUN_00e3a9cc;

    // Call engine cleanup function
    FUN_00ad9db0();

    // Check if subobject at +0x10 (offset 0x04) exists
    if (*(int*)((char*)this + 0x10) != 0) {
        // Call function pointer stored at +0x1c (offset 0x07)
        (*(void(__cdecl*)(int))*(int*)((char*)this + 0x1c))(*(int*)((char*)this + 0x10));
    }

    // Update vtable at +0x04
    *(int*)((char*)this + 4) = (int)&PTR_LAB_00e3aa7c;
    // Clear global flag
    DAT_01223484 = 0;
    // Finalize vtable to purecall
    this->vtable = (SomeClassVTable*)&PTR___purecall_00e3a958;
}