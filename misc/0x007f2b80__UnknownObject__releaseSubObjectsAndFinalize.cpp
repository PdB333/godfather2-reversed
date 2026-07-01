// FUNC_NAME: UnknownObject::releaseSubObjectsAndFinalize
// Reconstructed from address 0x007f2b80 - Cleanup function that releases two child objects and then finalizes self

#include <cstdint>

// Forward declaration of the vtable structure
struct UnknownObjectVTable;

// Structure representing an object with two child pointers and a vtable at offset 0x10
struct UnknownObject {
    void* child1;                // +0x00: pointer to first child object
    uint32_t padding1;           // +0x04: unused in this function
    uint32_t padding2;           // +0x08: unused
    void* child2;                // +0x0C: pointer to second child object (may be null)
    UnknownObjectVTable* vtable; // +0x10: pointer to virtual function table

    // Member function at 0x007f2b80
    void releaseSubObjectsAndFinalize();
};

// Virtual function table layout for this object
// Offsets: 0x04 = releaseObject, 0x0C = finalize
struct UnknownObjectVTable {
    void (*addRef)();                         // +0x00: likely AddRef (not called here)
    void (*releaseObject)(void* obj, int flags); // +0x04: release a child object with flags
    // ... other vtable entries ...
    void (*finalize)();                       // +0x0C: finalize/destroy self
};

// Implementation of the cleanup function
void UnknownObject::releaseSubObjectsAndFinalize() {
    // Call releaseObject on the first child (flags = 0)
    vtable->releaseObject(child1, 0);

    // If second child exists, release it as well
    if (child2 != nullptr) {
        vtable->releaseObject(child2, 0);
    }

    // Finalize the current object (may delete it)
    vtable->finalize();
}