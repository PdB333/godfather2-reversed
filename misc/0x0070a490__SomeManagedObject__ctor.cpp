// FUNC_NAME: SomeManagedObject::ctor
undefined4 __thiscall SomeManagedObject::ctor(byte allocFlag)
{
    // Call base class initializer (likely sets vtable and base members)
    initializeBase();
    // If the object was dynamically allocated (flag bit 0 set), deallocate memory as cleanup
    if ((allocFlag & 1) != 0) {
        // Deallocate this object's memory (size 0x7c = 124 bytes)
        deallocateMemory(this, 0x7c);
    }
    return this;
}