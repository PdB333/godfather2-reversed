// FUNC_NAME: UnknownClass::constructor
// Address: 0x00955ea0
// Role: Object constructor for a class derived from multiple base classes.
// Sets vtable pointers at offsets 0x00, 0x3C, 0x48, 0x50 (4 vtables).
// Calls base constructor and initialization, then optionally calls operator delete
// (size 0x170) if allocFlag indicates heap allocation (bit 0).

undefined4* __thiscall UnknownClass::constructor(UnknownClass* this, byte allocFlag)
{
    // Set primary vtable for this class
    *this = (undefined4*)&VTABLE_00d8c0b4;              // +0x00

    // Set additional vtable pointers (multiple inheritance)
    this->base1Vtable = (undefined4*)&VTABLE_00d8c0a4;  // +0x3C (offset 0x0F words)
    this->base2Vtable = (undefined4*)&VTABLE_00d8c0a0;  // +0x48 (offset 0x12 words)
    this->base3Vtable = (undefined4*)&VTABLE_00d8c09c;  // +0x50 (offset 0x14 words)

    // Call base class constructor with argument 0
    UnknownClass::baseConstructor(0);                   // FUN_00976360

    // Additional initialization for another base or member
    UnknownClass::initSubobject();                      // FUN_00473880

    // If heap-allocated, call operator delete with object size 0x170
    if ((allocFlag & 1) != 0) {
        UnknownClass::operatorDelete(this, 0x170);      // FUN_0043b960
    }

    return this;
}