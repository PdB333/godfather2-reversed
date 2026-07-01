// FUNC_NAME: SomeClass::constructor
// Function address: 0x00811220
// Role: Constructor for a class with vtable at offset 0, sub-object at offset 0x14

struct SomeClass {
    void** vtable; // +0x00
    // ... other members up to offset 0x3C
    void* field_0x3C; // +0x3C (likely interface vtable)
    // ... other members up to offset 0x48
    void* field_0x48; // +0x48 (likely interface vtable)
    // Sub-object at offset 0x14 (size unknown)
    uint8_t subObject[20]; // +0x14 (placeholder)
};

void __fastcall SomeClass::constructor(SomeClass* this) {
    // Set primary vtable pointer
    this->vtable = &PTR_FUN_00d72f04; // +0x00
    // Set secondary vtable pointers (multiple inheritance)
    this->field_0x3C = &PTR_LAB_00d72ef4; // +0x3C
    this->field_0x48 = &PTR_LAB_00d72ef0; // +0x48
    // Initialize sub-object at offset 0x14 (likely a base class or member)
    FUN_004086d0(&this->subObject); // +0x14
    FUN_00408310(&this->subObject); // +0x14
    // Global initialization call
    FUN_0046c640();
}