// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::SomeClass(SomeClass *this)
{
    // Set primary vtable at offset 0x00
    this->vtable = (void *)&PTR_FUN_00d8085c;
    // Set secondary vtable at offset 0x3C
    *(void **)((char *)this + 0x3C) = &PTR_LAB_00d8084c;
    // Set another vtable at offset 0x48
    *(void **)((char *)this + 0x48) = &PTR_LAB_00d80848;
    // Construct sub-object at offset 0x50
    FUN_004086d0((int *)((char *)this + 0x50));
    // Initialize sub-object at offset 0x50
    FUN_00408310((int *)((char *)this + 0x50));
    // Initialize another sub-object at offset 0x58
    FUN_00408310((int *)((char *)this + 0x58));
    // Global initialization
    FUN_0046c640();
}