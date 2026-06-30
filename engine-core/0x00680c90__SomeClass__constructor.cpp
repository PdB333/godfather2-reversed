// FUNC_NAME: SomeClass::constructor
int __thiscall SomeClass::constructor(void* this, byte flags)
{
    int* vtablePtrPtr;
    if (this == 0) {
        vtablePtrPtr = (int*)0x0;
    }
    else {
        vtablePtrPtr = (int*)((char*)this + 0x20); // +0x20: vtable pointer slot
    }
    *vtablePtrPtr = (int)&PTR_LAB_00d580d8; // Set vtable pointer
    g_someGlobalFlag = 0; // DAT_011298c8: global flag initialization
    FUN_007edfb0(); // Internal initialization
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this); // Possibly free or delete if allocated
    }
    return (int)this;
}