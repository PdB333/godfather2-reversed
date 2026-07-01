// FUNC_NAME: GameObject::~GameObject
// Address: 0x007D2960
// Role: Destructor for a game object with two sub-objects at offsets 0xB8 and 0x7C.
// Sets vtable to derived class, destroys sub-objects, then resets vtable to base class.

#include <cstdint>

// Forward declarations of known helper functions
void __fastcall releaseComponent(void* component); // FUN_004daf90 - likely a destructor or release
void __fastcall freeMemory(); // FUN_0080ea60 - likely operator delete or memory manager cleanup

class GameObject {
public:
    // Virtual table pointer (offset 0x00)
    void* vtablePtr;

    // Sub-object pointer at offset 0xB8 (0x2E * 4)
    void* subObjectAt_B8; // +0xB8

    // Sub-object pointer at offset 0x8C (0x23 * 4) - not used directly
    // Placeholder to maintain alignment

    // Sub-object pointer at offset 0x7C (0x1F * 4)
    void* subObjectAt_7C; // +0x7C

    // Vtable-like pointer at offset 0x74 (0x1D * 4)
    void* baseClassVtable; // +0x74

    // Constructor/destructor
    __thiscall ~GameObject() {
        // Set vtable to derived class (first vtable)
        this->vtablePtr = &PTR_LAB_00d6ee6c;

        // Destroy sub-object at offset 0xB8 if not null
        if (this->subObjectAt_B8 != NULL) {
            releaseComponent(this->subObjectAt_B8); // FUN_004daf90
        }

        // Temporarily set base class vtable to a functor (intermediate step)
        this->baseClassVtable = &PTR_FUN_00d6e930;

        // Destroy sub-object at offset 0x7C if not null
        if (this->subObjectAt_7C != NULL) {
            releaseComponent(this->subObjectAt_7C); // FUN_004daf90
        }

        // Restore base class vtable to final base class vtable
        this->baseClassVtable = &PTR_LAB_00d6ba68;

        // Set vtable to base class (final)
        this->vtablePtr = &PTR_LAB_00d6b95c;

        // Call global cleanup or deallocation
        freeMemory(); // FUN_0080ea60
    }
};

// In the actual binary, these pointers would be defined elsewhere.
// They represent virtual function tables for the class hierarchy.
void* PTR_LAB_00d6ee6c; // Derived class vtable
void* PTR_FUN_00d6e930; // Intermediate vtable pointer (function pointer)
void* PTR_LAB_00d6ba68; // Base class vtable
void* PTR_LAB_00d6b95c; // Final base class vtable (after destruction)