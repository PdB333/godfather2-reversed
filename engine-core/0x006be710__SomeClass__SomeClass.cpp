// FUNC_NAME: SomeClass::SomeClass
// Address: 0x006BE710
// Role: Constructor for a game object with multiple vtables and sub-objects (size 0x70).

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte allocFlag)
{
    // Set primary vtable pointer at offset 0x00
    this->vtable = (void*)&PTR_FUN_00d5eb60;
    // Set secondary vtable pointers at offsets 0x3C and 0x48
    *(void**)((char*)this + 0x3C) = (void*)&PTR_LAB_00d5eb50;
    *(void**)((char*)this + 0x48) = (void*)&PTR_LAB_00d5eb4c;

    // Initialize sub-object at offset 0x58 (param_1 + 0x16)
    void* subObj1 = (char*)this + 0x58;
    FUN_004086d0(subObj1);   // first-stage sub-object init (e.g., list head constructor)
    FUN_00408310(subObj1);   // second-stage sub-object init (e.g., link into manager)

    // Initialize additional sub-objects at offsets 0x60 and 0x68
    FUN_00408310((void*)((char*)this + 0x60));
    FUN_00408310((void*)((char*)this + 0x68));

    // Global one-time initialization (e.g., memory system)
    FUN_0046c640();

    // If allocation flag is set, deallocate this object (operator delete)
    if (allocFlag & 1) {
        FUN_0043b960(this, 0x70);
    }

    return this;
}