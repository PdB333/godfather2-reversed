//FUNC_NAME: SomeClass::constructor
// Address: 0x00782290
// Role: Constructor for a class with multiple vtables (likely multiple inheritance).
// Sets up vtable at +0x00, and additional vtables at +0x3C and +0x48.
// Calls base constructor (FUN_0077ea20) and optionally deletes object if allocFlag & 1.

// Note: The exact class name is unknown; placeholder "SomeClass" used.
// The base constructor at 0x0077ea20 is likely a parent class constructor.
// The function at 0x0043b960 is likely operator delete (size 0x90).

class SomeClass {
public:
    // Vtable pointers (offsets in bytes)
    void** vtable;          // +0x00
    // ... other members ...
    void* vtable2;          // +0x3C (offset 0x3C)
    void* vtable3;          // +0x48 (offset 0x48)
    // ... remaining members up to size 0x90 ...
};

SomeClass* __thiscall SomeClass::constructor(SomeClass* this, byte allocFlag) {
    // Set vtable pointer
    this->vtable = &PTR_FUN_00d695fc;   // Primary vtable
    // Set additional vtable pointers (likely for secondary interfaces)
    this->vtable2 = &PTR_LAB_00d695ec;  // +0x3C
    this->vtable3 = &PTR_LAB_00d695e8;  // +0x48

    // Call base class constructor (likely parent class)
    FUN_0077ea20();  // Base constructor

    // If the object was allocated with 'new' (allocFlag & 1), free it
    // This pattern is typical for constructors that handle both stack and heap allocation.
    if ((allocFlag & 1) != 0) {
        FUN_0043b960(this, 0x90);  // operator delete(this, size)
    }

    return this;
}