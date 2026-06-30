// FUNC_NAME: Entity::~Entity

// Destructor for Entity class (address 0x0050efe0).
// Cleans up child allocations and calls base destructor.
// Offsets:
//   +0x00: vtable
//   +0x10: m_pData1 (cleared)
//   +0x14: m_pData2 (cleared)
//   +0x24: m_pPhysics (pointer to physics object, bit 0x400 at +0x104)
//   +0x5B: m_state (byte, compared to 0x06)
//   +0x64: m_flags (zeroed if condition met)
//   +0x68: m_pAllocation (pointer to an allocated child, freed if non-null)
//   +0x6C: m_pOther (pointer to another object, freed if non-null)

#include <cstdint>

class EntityBase; // forward declaration for base destructor

class Entity {
public:
    // ...
    void __thiscall Destroy();  // virtual or explicit destructor call
    // Actually this is the destructor, so we'll implement it as such.
};

// Global memory manager (used to track live allocations)
extern uint8_t gMemoryManager[]; // DAT_01206880
// Vtables
extern void* gVtableDerived; // PTR_FUN_00e380f8
extern void* gVtableBase;    // PTR_FUN_00e37110
extern void* gVtableListNode; // PTR_LAB_01123be8 (used in list manipulation)

// Forward declarations for helper functions
void freeChildAllocation(void* ptr);         // FUN_009e7530
void cleanupMemoryPool();                     // FUN_009f01a0
void deleteOtherObject(void* ptr);           // FUN_009c8eb0
void baseDestructor();                       // FUN_0050bef0 (maybe EntityBase::~EntityBase)

void Entity::Destroy() {
    // Get the allocation pointer from offset +0x68
    void* pAllocation = *(void**)((uint8_t*)this + 0x68);
    
    // Set vtable to derived class's vtable (for proper destruction order)
    *(void**)this = &gVtableDerived;
    
    if (pAllocation != nullptr) {
        // If the allocation has a sub-object at +0x08, free it first
        if (*(void**)((uint8_t*)pAllocation + 0x08) != nullptr) {
            freeChildAllocation(pAllocation);
        }
        // Then perform some memory pool cleanup
        cleanupMemoryPool();
    }
    
    // Free the object at offset +0x6C if present
    void* pOther = *(void**)((uint8_t*)this + 0x6C);
    if (pOther != nullptr) {
        deleteOtherObject(pOther);
    }
    
    // Conditionally clear flags at offset +0x64
    // Checks state byte at +0x5B and a flag in the physics object
    uint8_t state = *(uint8_t*)((uint8_t*)this + 0x5B);
    void* pPhysics = *(void**)((uint8_t*)this + 0x24);
    if ((state == 0x06) && (*(uint32_t*)((uint8_t*)pPhysics + 0x104) & 0x400) != 0) {
        *(int*)((uint8_t*)this + 0x64) = 0;  // Clear flags
    }
    
    // Call the base class destructor
    baseDestructor();
    
    // Now set vtable to base class vtable (for safety)
    *(void**)this = &gVtableBase;
    
    // Re-fetch the allocation pointer (it may have been modified by base destructor?)
    void* pAllocation2 = *(void**)((uint8_t*)this + 0x68);
    if (pAllocation2 != nullptr) {
        // Add the allocation to the global memory manager's list
        // The memory manager seems to have a list head at offset +0x14
        int** pListSlot = (int**)(gMemoryManager + 0x14);
        *(void**)pListSlot = &gVtableListNode;
        (*pListSlot)++;         // Move to next slot
        *(int*)*pListSlot = (int)pAllocation2;
        (*pListSlot)++;
        
        // Clear the data pointers at +0x10 and +0x14
        *(void**)((uint8_t*)this + 0x10) = nullptr;
        *(void**)((uint8_t*)this + 0x14) = nullptr;
    }
    
    return;
}