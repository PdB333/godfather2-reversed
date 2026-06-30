// FUNC_NAME: EARSObject::EARSObject

// Function at 0x00596640 - Base class constructor for EARS objects.
// Initializes vtable pointer and calls base initializer.
class EARSObject {
public:
    void* vtable; // +0x00 (vtable pointer)
    // Additional members follow...
    EARSObject();
};

// Base initializer function (likely parent constructor)
extern void FUN_00596650(void);

// External vtable symbol for the base class
extern void* PTR_FUN_00e3adf0;

// Constructor implementation
EARSObject::EARSObject() {
    // Set vtable to class-specific vtable (PTR_FUN_00e3adf0)
    this->vtable = (void*)&PTR_FUN_00e3adf0; // +0x00
    // Call base class initializer (parent constructor)
    FUN_00596650();
}