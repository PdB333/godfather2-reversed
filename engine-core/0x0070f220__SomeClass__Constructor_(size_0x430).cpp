// FUNC_NAME: SomeClass::Constructor (size 0x430)
// Function address: 0x0070f220
// Role: Constructor for an object of size 0x430 bytes.
// Calls base initializer and optionally registers the object (if heap-allocated).

// Note: The calling convention is __thiscall. param_2 is a flag indicating
// whether the object was allocated via operator new (bit 0 set).
// When set, FUN_0043b960 is called to register the object (e.g., add to a manager list).

class SomeClass; // Forward declaration

// Forward declarations of helper functions (from Ghidra)
// These would be defined elsewhere and should be renamed accordingly.
void __thiscall BaseConstructor(SomeClass* this); // FUN_0070e5e0
void __thiscall ObjectRegister(SomeClass* this, int size); // FUN_0043b960

// Constructor
SomeClass* __thiscall SomeClass::Constructor(SomeClass* this, unsigned char allocFlag) {
    BaseConstructor(this);
    if ((allocFlag & 1) != 0) {
        ObjectRegister(this, 0x430);
    }
    return this;
}