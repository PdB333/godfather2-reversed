// FUNC_NAME: Handle::Handle
// Reconstructed constructor for a handle/reference class that binds to an element in a manager's array.
// The handle stores a pointer to the manager (param_2), an index (param_4), and a type ID (param_3).
// It validates that the element at the given index has the expected type ID.

#include <cstdint>

// Forward declarations
class Manager; // unknown structure, but has at +0x4 a pointer to an array of elements (size 0x34 each) and at +0x8 a count (uint32_t)

class Handle {
public:
    // Vtable pointers (from Ghidra data)
    static const void* baseVtable;   // PTR_FUN_00e35c28
    static const void* derivedVtable; // PTR_FUN_00d7aed0

    // Fields (offsets in bytes)
    void* vtable;          // +0x0
    uint32_t index;        // +0x4  (param_4 stored here)
    Manager* manager;      // +0x8  (param_2 stored here)
    uint32_t typeId;       // +0xC  (param_3 stored here)

    // Constructor
    Handle(Manager* mgr, uint32_t typeId, uint32_t index) {
        // Step 1: Set base vtable
        this->vtable = baseVtable;

        // Step 2: Initialize manager and index
        if (mgr == nullptr || *(uint32_t*)((uint8_t*)mgr + 8) == 0) {
            this->manager = nullptr;
            this->index = 0;
        } else {
            this->manager = mgr;
            this->index = index;
        }

        // Step 3: Set derived vtable (override)
        this->vtable = derivedVtable;

        // Step 4: Store type ID
        this->typeId = typeId;

        // Step 5: Validate that the element at the index has the expected type ID
        if (this->manager != nullptr) {
            uint32_t count = *(uint32_t*)((uint8_t*)this->manager + 8);
            if (this->index < count) {
                // Get pointer to element array (at manager + 0x4)
                uint8_t* elementArray = *(uint8_t**)((uint8_t*)this->manager + 4);
                // Each element is 0x34 bytes; the first field (offset 0) is the type ID
                uint32_t actualTypeId = *(uint32_t*)(elementArray + this->index * 0x34);
                if (actualTypeId != this->typeId) {
                    // Type mismatch – call error handler
                    FUN_008b3f60(); // likely assertion or error log
                }
            }
        }
    }
};

// Static vtable pointers (defined elsewhere in the binary)
const void* Handle::baseVtable = (void*)0x00e35c28;
const void* Handle::derivedVtable = (void*)0x00d7aed0;

// External error handler (FUN_008b3f60)
extern void FUN_008b3f60();