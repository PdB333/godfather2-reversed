// FUNC_NAME: EAObject::~EAObject
// Address: 0x004ff3d0
// Destructor for EAObject. Handles sub-object destruction, global cleanup, and returns memory to pool.

#include <cstdint>

class EAObject {
public:
    uint32_t* vtable;       // +0x00: virtual table pointer
    uint32_t field_4;       // +0x04
    uint32_t field_8;       // +0x08
    uint32_t field_C;       // +0x0C
    uint32_t field_10;      // +0x10: pointer to memory block to be freed
    uint32_t field_14;      // +0x14: associated size or link
    // ... other fields up to +0x28
    uint32_t field_28;      // +0x28: pointer to a sub-object that needs separate destruction

    ~EAObject();
};

// Vtable symbols (defined elsewhere)
extern uint32_t PTR_FUN_00e37b70[];   // base vtable
extern uint32_t PTR_FUN_00e37110[];   // zombie vtable (prevents double deletion)
extern uint32_t PTR_LAB_01123be8[];   // sentinel or list terminator

// Global memory pool base address (DAT_01206880)
extern uint8_t g_memoryPoolBase;

// Forward declarations of helper functions
void FUN_004ff430();   // sub-object destructor
void FUN_004ebba0();   // global cleanup (e.g., unregister from manager)

void EAObject::~EAObject() {
    // Step 1: Set vtable to base vtable to allow correct virtual dispatch during destruction
    this->vtable = PTR_FUN_00e37b70;

    // Step 2: Destroy sub-object if present
    if (this->field_28 != 0) {
        FUN_004ff430();
    }

    // Step 3: Perform global cleanup (e.g., unregister from system)
    FUN_004ebba0();

    // Step 4: Set vtable to zombie vtable to prevent accidental virtual calls after destruction
    this->vtable = PTR_FUN_00e37110;

    // Step 5: Return the allocated memory block (at offset +0x10) to the free list
    if (this->field_10 != 0) {
        // Get pointer to the free list head from global pool (offset +0x14)
        uint32_t** freeListHead = reinterpret_cast<uint32_t**>(
            reinterpret_cast<uint8_t*>(&g_memoryPoolBase) + 0x14);

        // Push the block onto the free list (list is an array of pointers)
        **freeListHead = reinterpret_cast<uint32_t>(PTR_LAB_01123be8); // write sentinel
        *freeListHead = reinterpret_cast<uint32_t*>(
            reinterpret_cast<uint8_t*>(*freeListHead) + 4);          // advance head
        **freeListHead = this->field_10;                              // store block address
        *freeListHead = reinterpret_cast<uint32_t*>(
            reinterpret_cast<uint8_t*>(*freeListHead) + 4);          // advance head again

        // Clear the memory block fields in this object
        this->field_10 = 0;
        this->field_14 = 0;
    }
}