// FUNC_NAME: EARSObject::EARSObject
// Constructor for a derived EARS object. Sets up base class via vtable pointer swap and then installs own vtable.
// Address: 0x0046a780

// Forward declarations for referenced vtables (external)
extern void* PTR_FUN_00e324a8;   // Base class vtable
extern void* PTR_LAB_00e30ea0;   // Derived class vtable

// Base class constructor (must be declared or extern)
extern void __fastcall FUN_0043e380(void* thisPtr); // base class constructor

class EARSBase {
public:
    void* vtable; // +0x00: virtual function table pointer
    // ... additional members follow in derived classes
};

class EARSObject : public EARSBase {
public:
    EARSObject();
    // ... derived members
};

// Constructor - sets vtable to base, calls base constructor, then installs own vtable
EARSObject::EARSObject() {
    // Point vtable to base class vtable before calling base constructor
    this->vtable = &PTR_FUN_00e324a8;
    // Call base class constructor (e.g., EARSBase::EARSBase())
    FUN_0043e380(this);
    // Overwrite vtable with derived class's vtable
    this->vtable = &PTR_LAB_00e30ea0;
}