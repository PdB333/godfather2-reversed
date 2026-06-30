// FUNC_NAME: SomeClass::SomeClass
// Constructor for a class with virtual base. Address: 0x004c9210
// Sets two vtable pointers, calls base constructor, sets main vtable, resets a global flag.
// If allocFlag & 1, calls a deallocation function (likely operator delete or cleanup).
void* __thiscall SomeClass::SomeClass(SomeClass* this, byte allocFlag)
{
    // Set base class vtable pointer offset? (vtable at +0x00)
    this->vfptr = (VTableType*)&PTR_FUN_00e36614;
    // Set secondary vtable pointer (maybe for virtual base) at +0x04
    this->someOtherVfptr = (VTableType*)&PTR_LAB_00e36618;

    // Call base class constructor
    FUN_004083d0(this);

    // Set actual derived class vtable
    this->vfptr = (VTableType*)&PTR_LAB_00e36628;

    // Initialize global singleton flag to 0
    g_someGlobalFlag = 0;   // DAT_01223404

    if ((allocFlag & 1) != 0)
    {
        // If allocated via new (flag bit 0 set), free memory (constructor cleanup)
        FUN_009c8eb0(this);
    }

    return this;
}