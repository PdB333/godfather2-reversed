//FUNC_NAME: BaseObject::BaseObject
// Address: 0x0081ffd0
// Constructor for a class with multiple vtables. Sets up vtable pointers, calls base class constructor, and optionally deallocates memory if allocFlag is set.

BaseObject* __thiscall BaseObject::BaseObject(BaseObject* this, byte allocFlag)
{
    // Set up vtable pointers for multiple inheritance
    this->vtable = &vtable_00d73364;          // +0x00
    this->vtable2 = &vtable2_00d73354;        // +0x3C (offset 0x0F * 4)
    this->vtable3 = &vtable3_00d73350;        // +0x48 (offset 0x12 * 4)

    // If a resource pointer at offset 0xE8 (0x3A * 4) is non-null, call its destructor via function pointer at offset 0xF4 (0x3D * 4)
    if (this->resourcePtr != nullptr)          // +0xE8
    {
        // Call the destructor function stored at +0xF4
        (this->destructorFunc)(this->resourcePtr); // +0xF4
    }

    // Call base class constructor (global initialization)
    baseClassConstructor();                    // FUN_008339d0

    // If allocFlag has bit 0 set, deallocate this object with size 0xF8
    if ((allocFlag & 1) != 0)
    {
        customDelete(this, 0xF8);             // FUN_0043b960
    }

    return this;
}