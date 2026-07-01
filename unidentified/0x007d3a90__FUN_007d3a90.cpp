// FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x007d3a90
// Role: Destructor that releases a pointer member (offset +0x4) and sets vtable to base class vtable

struct SomeClass {
    void** vtable;                // +0x0: virtual function table pointer
    SomeOtherType* memberPointer; // +0x4: pointer to a dynamically allocated object
};

void __thiscall SomeClass::~SomeClass(SomeClass* this) {
    // Destroy the member object if it exists
    if (this->memberPointer != nullptr) {
        FUN_004daf90(this->memberPointer);  // likely member's destructor or release
    }
    // Set vtable to base class vtable to prevent further virtual calls during base destruction
    this->vtable = &PTR_LAB_00e2f0c0;
}