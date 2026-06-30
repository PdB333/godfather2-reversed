// FUNC_NAME: SomeObject::initializeBaseClasses
// Function address: 0x006a2540
// Role: Constructor helper that initializes multiple base class subobjects within a derived object.
// For each of 6 base classes (at offsets 0, 8, 16, 24, 32, 40), it sets the vtable pointer to a common
// default (PTR_FUN_00d5d3c0) and calls the base constructor (FUN_006a3720).

void __fastcall initializeBaseClasses(void* thisPtr)
{
    // Each base subobject is 8 bytes: vtable pointer (4) + padding/other field (4).
    // Offsets: +0x00, +0x08, +0x10, +0x18, +0x20, +0x28

    // Base 1 at offset 0
    *(int*)((char*)thisPtr + 0x00) = (int)&PTR_FUN_00d5d3c0; // set vtable
    FUN_006a3720((char*)thisPtr + 0x00);                     // call base constructor

    // Base 2 at offset 8
    *(int*)((char*)thisPtr + 0x08) = (int)&PTR_FUN_00d5d3c0;
    FUN_006a3720((char*)thisPtr + 0x08);

    // Base 3 at offset 16 (0x10)
    *(int*)((char*)thisPtr + 0x10) = (int)&PTR_FUN_00d5d3c0;
    FUN_006a3720((char*)thisPtr + 0x10);

    // Base 4 at offset 24 (0x18)
    *(int*)((char*)thisPtr + 0x18) = (int)&PTR_FUN_00d5d3c0;
    FUN_006a3720((char*)thisPtr + 0x18);

    // Base 5 at offset 32 (0x20)
    *(int*)((char*)thisPtr + 0x20) = (int)&PTR_FUN_00d5d3c0;
    FUN_006a3720((char*)thisPtr + 0x20);

    // Base 6 at offset 40 (0x28)
    *(int*)((char*)thisPtr + 0x28) = (int)&PTR_FUN_00d5d3c0;
    FUN_006a3720((char*)thisPtr + 0x28);

    return;
}