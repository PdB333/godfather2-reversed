// FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x004ec000
// Role: Destructor with optional memory deallocation

// Note: Vtable pointers at 0x00e372b4 and 0x00e3729c.
// param_2 is a delete flag (bit 0 indicates whether to free memory).

void __thiscall SomeClass::~SomeClass(SomeClass* this, byte deleteFlag)
{
    // Set vtable to first destructor vtable
    *(int**)this = &PTR_FUN_00e372b4;

    // If there is a subobject/resource at offset +0x20 (param_1[8]), call its destructor
    if (this->field_0x20 != 0) {
        // Call destructor via global allocator's vtable (DAT_01194538 + 4)
        (**(code**)(*DAT_01194538 + 4))(this->field_0x20, 0);
    }

    // Set vtable to second destructor vtable (base class?)
    *(int**)this = &PTR_LAB_00e3729c;

    // If delete flag is set, deallocate memory
    if ((deleteFlag & 1) != 0) {
        int* allocator = (int*)FUN_009c8f80(); // Get memory allocator
        (**(code**)(*allocator + 4))(this, 0); // Free this object
    }
}