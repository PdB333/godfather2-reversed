// FUNC_NAME: SomeClass::~SomeClass

// File: SomeClass destructor
// Address: 0x00765010
// Role: Destructor with memory deallocation flag
// Class layout: vtable at +0x00, owned pointer at +0x64 (param_1[0x19])

#include <cstdint>

// Forward declare external functions (from unknown translation units)
void destroyOwnedComponent(void* ownedPtr);  // 0x004daf90
void globalCleanup();                         // 0x004ac1e0
void operatorDelete(void* ptr);              // 0x00624da0 (likely operator delete)

// Vtable reference (address 0x00d65684)
extern void* gVtable_SomeClass;

class SomeClass {
public:
    // Vtable pointer at offset 0x00
    void* vtable;

    // ... other members ...

    // Pointer at offset 0x64 (index 0x19)
    void* ownedComponent;  // e.g., a child object or resource

    // Destructor: destroys owned subobject, calls global cleanup, optionally frees memory
    void destroy(uint8_t freeFlag) {
        // Restore vtable (adjustment for virtual base / scalar deleting destructor)
        this->vtable = &gVtable_SomeClass;

        // If owned component exists, destroy it
        if (this->ownedComponent != nullptr) {
            destroyOwnedComponent(this->ownedComponent);
        }

        // Global or static cleanup
        globalCleanup();

        // If flag bit 0 is set, free the memory
        if (freeFlag & 1) {
            operatorDelete(this);
        }
    }
};