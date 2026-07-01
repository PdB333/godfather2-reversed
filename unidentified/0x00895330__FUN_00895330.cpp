// FUNC_NAME: SomeClass::SomeClass
void __thiscall SomeClass::SomeClass(SomeClass *this)
{
    // Set virtual function table pointer (offset +0x00)
    *(int *)this = (int)&SomeClass_vtable;

    // Initialize data at +0x3C (offset 0xf * 4)
    *(int *)((char *)this + 0x3C) = (int)&PTR_LAB_00d778e4;

    // Initialize data at +0x48 (offset 0x12 * 4)
    *(int *)((char *)this + 0x48) = (int)&PTR_LAB_00d778e0;

    // Call base class constructor or additional initialization via global function pointer
    ((void (*)())(PTR_FUN_00d7791c))();

    // Register with three global lists/objects (likely manager singletons)
    FUN_00408310((void *)&DAT_0112e31c);
    FUN_00408310((void *)&DAT_0112e314);
    FUN_00408310((void *)&DAT_01218048);

    // Perform final initialization (e.g., subsystem startup)
    FUN_0046c640();
}