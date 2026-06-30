// FUNC_NAME: UnknownClass::constructor
int __thiscall UnknownClass::constructor(UnknownClass* this, byte flags)
{
    // Set vtable pointer at offset +0x20
    if (this == 0) {
        *(void**)0 = (void*)&PTR_LAB_00d580fc; // potential null dereference if this is null
    } else {
        *(void**)((int)this + 0x20) = (void*)&PTR_LAB_00d580fc;
    }
    // Reset global initialization flag
    DAT_01129960 = 0;
    // Call base constructor or common initialization routine
    FUN_007edfb0();
    // If the object was dynamically allocated (flag bit 0 set), call cleanup/destructor
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);
    }
    return (int)this;
}