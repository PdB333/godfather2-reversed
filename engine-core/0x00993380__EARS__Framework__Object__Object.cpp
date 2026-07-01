// FUNC_NAME: EARS::Framework::Object::Object
EARS::Framework::Object * __thiscall EARS::Framework::Object::Object(EARS::Framework::Object *this, byte allocFlag)
{
    // Set virtual table pointer
    this->vfTable = &PTR_FUN_00d92178; // +0x00

    // Set secondary class data pointer (likely static vtable or RTTI)
    this->classData = &PTR_LAB_00d92150; // +0x04

    // Initialize two member pointers at offset 0x4C (decompiler shows two assignments to same index, possibly a bug or union)
    this->field_4C_first = &PTR_LAB_00d9214c; // +0x4C
    this->field_4C_second = &PTR_LAB_00d92148; // +0x4C (overwrites previous, maybe intended for different member?)

    // Clear global initialization flag
    DAT_0113000c = 0; // global static flag

    // Call base initialization routine
    FUN_005c16e0(); // likely initializes base subsystem

    // If allocFlag bit 0 is set, call deallocation/cleanup function on this object
    if ((allocFlag & 1) != 0) {
        FUN_005c4480(this); // possibly destructor or memory manager cleanup
    }

    return this;
}