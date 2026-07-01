// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass(SomeClass* this) {
    // Set vtable to destructor vtable
    this->vtable = &PTR_FUN_00d73190;
    // Set some pointer to a label (likely base class vtable or cleanup function)
    this->field_0x08 = &PTR_LAB_00d7318c;

    // Call static destructor for a global object
    FUN_0049c7f0(&DAT_00d7317c);

    // Loop over an array of resources (count at offset +0x10)
    int count = this->field_0x10;
    while (count-- > 0) {
        FUN_00604da0(); // Free or release each resource
    }

    // If there is a dynamically allocated array (offset +0x0C), free it
    if (this->field_0x0C != 0) {
        FUN_009c8f10(this->field_0x0C);
    }

    // Update pointer to another label (likely base class vtable)
    this->field_0x08 = &PTR_LAB_00d73188;

    // Reset global singleton flag
    DAT_011298dc = 0;

    // Final cleanup
    FUN_0049c640();
}