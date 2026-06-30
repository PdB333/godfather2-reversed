// FUNC_NAME: SimObject::SimObject
// Function address: 0x004192b0
// Role: Constructor for SimObject (EARS engine base class)
// Sets vtable pointer, calls base constructor, then optionally calls postConstruct if initFlags bit 0 set.

#include <cstdint>

// Forward declarations and structures for context
struct SimObject_vtable; // external

struct EARSObject {
    void **vtablePtr; // +0x00
    // other EARSObject members...
};

struct SimObject : public EARSObject {
    // virtual destructor, etc.
};

// Decompiled constructor
SimObject * __thiscall SimObject::SimObject(SimObject *this, uint8_t initFlags) {
    // Set vtable pointer to class-specific vtable (offset 0x00)
    this->vtablePtr = (void **)&SimObject_vtable;

    // Call base class constructor (EARSObject base)
    ((void (__thiscall *)(EARSObject *))0x00418740)(this);

    // If bit 0 is set, perform additional initialization (e.g., allocation, registration)
    if (initFlags & 1) {
        // Post-construction step (may handle memory or manager registration)
        ((void (__thiscall *)(SimObject *))0x009c8eb0)(this);
    }

    return this;
}