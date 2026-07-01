// FUNC_NAME: EARSObject::EARSObject
undefined4* __thiscall EARSObject::EARSObject(undefined4* this, byte owningFlag)
{
    // Set primary vtable: +0x00 points to vtable at 0x00d7d588
    *this = &PTR_FUN_00d7d588;
    // Set secondary vtable at offset +0x4C (0x13 * 4) to a different vtable
    this[0x13] = &PTR_LAB_00d7d578;

    // Initialize two embedded sub-objects at offsets +0x58 and +0x68
    // These are likely RefCounted or similar EA base objects
    FUN_00408310(this + 0x16);  // SubObject1 at this+0x58
    FUN_00408310(this + 0x1a);  // SubObject2 at this+0x68

    // Initialize global/static state (singleton or engine-wide data)
    FUN_004083d0();
    FUN_008d2680();

    // If the owning flag indicates this object was heap-allocated,
    // call the operator delete (likely for cleanup on construction failure)
    if ((owningFlag & 1) != 0) {
        FUN_009c8eb0(this);  // operator delete
    }

    return this;
}