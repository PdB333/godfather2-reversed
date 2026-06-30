// FUNC_NAME: SomeClass::Constructor
// Address: 0x00760190
// This function appears to be a constructor for a class that inherits from a base with a vtable.
// It initializes fields, stores parameters, and optionally releases a subobject at offset +0x04.

__thiscall SomeClass* SomeClass::Constructor(void* param2, void* param3, void* param4, void* param5, uint flags, void* param7)
{
    // Set vtable pointer (class' virtual function table)
    this->vtable = &PTR_FUN_00d653ec;

    // Zero-initialize member fields
    this->field04 = 0;          // +0x04: subobject pointer
    this->field08 = 0;          // +0x08
    this->field0C = 0;          // +0x0C
    this->field10 = 0;          // +0x10
    this->field14 = 0;          // +0x14
    this->field18 = 0;          // +0x18
    this->field20 = 0;          // +0x20
    this->field24 = 0;          // +0x24
    this->field38 = 0;          // +0x38 (flags field, initially zero)

    // Store param2 at offset +0x1C
    this->field1C = param2;

    // If subobject pointer is non-null, release it and set to null
    if (this->field04 != 0) {
        FUN_004daf90(this->field04);   // Likely a release/destructor function
        this->field04 = 0;
    }

    // Re-initialize field0C (maybe intentional double-zeroing due to compiler optimization)
    this->field0C = 0;

    // Store remaining parameters
    this->field28 = param4;     // +0x28
    this->field2C = param3;     // +0x2C
    this->field34 = param5;     // +0x34
    this->field38 |= flags;     // +0x38: OR in flags
    this->field30 = param7;     // +0x30

    return this;
}