// FUNC_NAME: Entity::Constructor

#include <cstddef>

// Forward declarations for referenced functions
void registerObject(uint32_t classId);
void* secondStageInit(void* obj);

class Entity {
public:
    void** vtable;        // +0x00
    void* base2Ptr;       // +0x04
    // Additional members follow at +0x08
};

// Global state flag
extern int gGlobalStateFlag = 0;

// External vtable tables
extern void* const PTR_FUN_00d6baa0;
extern void* const PTR_LAB_00d6ba9c;
extern void* const PTR_LAB_00d6ba98;
extern void* const PTR_LAB_00e30fe0;

// __thiscall constructor
Entity* Entity::Constructor(Entity* thisPtr, byte allocFlags) {
    // Set initial vtable and base class pointer
    thisPtr->vtable = &PTR_FUN_00d6baa0;   // Primary vtable placeholder
    thisPtr->base2Ptr = &PTR_LAB_00d6ba9c; // Second base vtable

    // Perform base class registration with unique class ID
    registerObject(0x7b80c13a); // Class ID for Entity base

    // Update second base vtable pointer after registration
    thisPtr->base2Ptr = &PTR_LAB_00d6ba98;

    // Reset global state flag
    gGlobalStateFlag = 0;

    // Finalize primary vtable to the actual derived class vtable
    thisPtr->vtable = &PTR_LAB_00e30fe0;

    // If allocation flag indicates secondary initialization, call it
    if (allocFlags & 1) {
        secondStageInit(thisPtr);
    }

    return thisPtr;
}