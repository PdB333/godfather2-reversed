// FUNC_NAME: SomeClass::constructor
SomeClass* __thiscall SomeClass::constructor(SomeClass* this, byte param_2)
{
    // Set vtable pointer (base class or most derived)
    *this = &PTR_FUN_00d74178;   // +0x00: vtable

    // Set additional vtable/function pointers for multiple inheritance
    this[0xf] = &PTR_LAB_00d74164;   // +0x3C: function table for derived interface?
    this[0x12] = &PTR_LAB_00d74160;  // +0x48: function table for another base?
    this[0x56] = &PTR_LAB_00d7415c;  // +0x158: vtable or function pointer
    this[0x56] = &PTR_LAB_00d74158;  // Note: overwrites previous – possibly intended for different offset (Ghidra artifact)

    // Global static flag – reset to 0
    DAT_0112a694 = 0;

    // Call base class constructor or other initialization
    FUN_0083f2f0();

    // If the object was heap-allocated (flag set), delete it (operator delete with size 0x15c)
    if ((param_2 & 1) != 0) {
        FUN_0043b960(this, 0x15c);
    }

    return this;
}