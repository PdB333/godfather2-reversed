// FUNC_NAME: SomeDerivedClass::SomeDerivedClass
// Address: 0x008564e0
// Role: Constructor for a derived class. Calls base constructor, sets vtable, and conditionally calls a cleanup function based on a flag.

class SomeDerivedClass : public SomeBaseClass {
public:
    // Constructor takes a byte flag (param_2). If bit 0 is set, calls a cleanup function (likely for copy/move semantics).
    SomeDerivedClass(byte flag);
};

// Base class constructor (FUN_00855830) - assumed to be a no-arg constructor
void SomeBaseClass::SomeBaseClass();

// External function (FUN_009c8eb0) - possibly a destructor or copy helper
void SomeCleanupFunction(SomeDerivedClass* obj);

SomeDerivedClass::SomeDerivedClass(byte flag) {
    // Call base class constructor
    SomeBaseClass::SomeBaseClass();

    // Set vtable pointer (PTR_LAB_00e355fc) - points to derived class vtable
    this->vtable = &SomeDerivedClass_vtable; // +0x00

    // If flag bit 0 is set, perform additional cleanup (e.g., for temporary objects)
    if (flag & 1) {
        SomeCleanupFunction(this);
    }
}