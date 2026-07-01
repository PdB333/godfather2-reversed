// FUNC_NAME: SomeClass::SomeClass
// Function at 0x008cc840: Constructor for a class with two vtable stages (base then derived)
// This is likely a derived class constructor, initializing base class vtable, then conditionally
// initializing a sub-object at offset +0x4, then setting the derived class vtable.

class SomeClass : public BaseClass {
public:
    // Base class vtable pointer at offset 0, derived vtable pointer after construction
    void* __vfptr; // +0x0

    // Sub-object at offset 0x4 (conditional initialization)
    // Type unknown, but likely a small struct or another object
    char subObject[4]; // +0x4 (example size, adjust based on context)

    // Constructor
    void __thiscall SomeClass::SomeClass() {
        // Step 1: Set base class vtable (if any)
        // This is typical for constructor chaining: base class vtable first
        this->__vfptr = &PTR_FUN_00d7c598; // Base class vtable

        // Step 2: Check if a condition (e.g., memory allocation succeeded) is true
        // FUN_006101a0() likely returns a flag or pointer to some resource
        int iVar1 = FUN_006101a0(); // Could be IsMemoryAvailable() or similar
        if (iVar1 != 0) {
            // Step 2b: Initialize sub-object at offset 4 if condition holds
            // FUN_00610100(this + 4) likely initializes a sub-object (e.g., a string, list, or another object)
            FUN_00610100(this + 4);
        }

        // Step 3: Overwrite vtable with derived class vtable to finalize the object
        this->__vfptr = &PTR_LAB_00e2f638; // Derived class vtable
    }
};