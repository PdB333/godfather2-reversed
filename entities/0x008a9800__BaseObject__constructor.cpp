// FUNC_NAME: BaseObject::constructor
// Address: 0x008a9800
// Role: Constructor for a base class with dual vtable pointers (EA EARS framework)

#include <cstdint>

// External helper functions (from the EARS runtime)
extern void* __cdecl allocateSomething(void);          // FUN_00481610 – allocate sub-object
extern void  __cdecl baseInitialize(int, int);         // FUN_0064d390 – initialize base subsystem
extern void  __cdecl subObjectInit(void*);             // FUN_00454a10 – additional init

// Vtable symbols (from ROM)
extern void* PTR_LAB_00e317dc;   // Base vtable (before derived)
extern void* PTR_LAB_00d79d9c;   // Derived primary vtable
extern void* PTR_LAB_00d79bc0;   // Secondary vtable (interface)
extern void  LAB_008a8930;       // Member function (destructor or method)

class BaseObject {
public:
    // Known offsets (relative to this):
    // +0x00 : void* vtable (primary)
    // +0x14 : void* selfPtr (points to +0x28)
    // +0x18 : uint32_t flags
    // +0x24 : uint32_t count (init to 1)
    // +0x28 : void* vtableDerived2 (secondary vtable)
    // +0x30 : void* funcPtr (member function)
    // +0x34 : void* somePtr (init to 0)

    void* vtable;                // +0x00
    uint8_t _pad0[0x14 - 0x04]; // padding
    void* selfPtr;               // +0x14
    uint32_t flags;              // +0x18
    uint8_t _pad1[0x24 - 0x1C]; // padding
    uint32_t count;              // +0x24
    void* vtableDerived2;        // +0x28
    void* funcPtr;               // +0x30
    void* somePtr;               // +0x34
};

BaseObject* __thiscall BaseObject::constructor(BaseObject* this, int param) {
    void* subObj = nullptr;
    if (param != 0) {
        subObj = allocateSomething();  // Allocate sub-object if requested
    }
    baseInitialize(0, 1);             // Common base initialization

    // Set initial base vtable
    this->vtable = &PTR_LAB_00e317dc;
    this->flags = 0;

    subObjectInit(subObj);            // Initialize sub-object (if any)

    this->count = 1;                  // Reference count or usage count

    // Switch to derived vtables
    this->vtable = &PTR_LAB_00d79d9c;
    this->vtableDerived2 = &PTR_LAB_00d79bc0;
    this->funcPtr = &LAB_008a8930;   // Virtual method pointer
    this->somePtr = nullptr;

    // Self-referencing pointer: points to secondary vtable slot
    this->selfPtr = &this->vtableDerived2;

    return this;
}