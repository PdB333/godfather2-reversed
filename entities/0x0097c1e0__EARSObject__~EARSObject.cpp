// FUNC_NAME: EARSObject::~EARSObject
// Function at 0x0097c1e0: Destructor for an EA EARS engine object that releases owned resources.
// The object contains three pointers at offsets 0x00, 0x04, and 0x08.
// +0x00 and +0x04 point to objects with virtual function tables (released via first vtable entry with argument 1).
// +0x08 is a resource handle freed by external helper functions.

#include <cstdint>

// Forward declarations for external cleanup functions
extern void FUN_009e71f0(void* obj, void* resource);
extern void FUN_009f01a0();

// Base class for objects that support a "release" virtual function
struct Releaseable {
    virtual void release(int flag) = 0;
};

// Represents the object being destroyed
struct EARSObject {
    Releaseable* member0;  // +0x00 - pointer to a Releaseable object
    Releaseable* member1;  // +0x04 - pointer to another Releaseable object
    void*       member2;  // +0x08 - pointer to a resource (not a Releaseable)
};

void __thiscall EARSObject::~EARSObject() {
    // Release member2 using external functions
    if (member2 != nullptr) {
        FUN_009e71f0(this, member2);
        FUN_009f01a0();
        member2 = nullptr;
    }

    // Release member1 via its virtual function
    if (member1 != nullptr) {
        member1->release(1);  // Calls first vtable entry with argument 1
        member1 = nullptr;
    }

    // Release member0 via its virtual function
    if (member0 != nullptr) {
        member0->release(1);
        member0 = nullptr;
    }
}