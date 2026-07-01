// FUNC_NAME: SomeGameObject::SomeGameObject
// Address: 0x0088e000
// Role: Constructor for a game object with multiple vtable pointers and a sub-object at offset 0x50.

void __thiscall SomeGameObject::SomeGameObject(SomeGameObject* this) {
    // Set primary vtable pointer (offset 0x00)
    *(void**)this = (void*)&PTR_FUN_00d77170;

    // Set secondary vtable pointer at offset 0x3C (0xF * 4)
    *(void**)((char*)this + 0x3C) = (void*)&PTR_LAB_00d77160;

    // Set tertiary vtable pointer at offset 0x48 (0x12 * 4)
    *(void**)((char*)this + 0x48) = (void*)&PTR_LAB_00d7715c;

    // Initialize sub-object at offset 0x50 (this + 0x14)
    // FUN_004086d0 and FUN_00408310 are likely constructors for base classes or members
    FUN_004086d0((char*)this + 0x50);
    FUN_00408310((char*)this + 0x50);

    // Global initialization call (e.g., reference counting, singleton setup)
    FUN_0046c640();
}