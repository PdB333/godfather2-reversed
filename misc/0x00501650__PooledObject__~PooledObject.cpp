// FUNC_NAME: PooledObject::~PooledObject
#include <cstdint>

// Global memory pool manager base address (inferred from Ghidra)
extern uint32_t DAT_01206880;

// Sentinel pointer used in free list (from Ghidra)
extern void* PTR_LAB_01123be8;

// Vtable pointer for base class (after destruction)
extern void* PTR_FUN_00e37110;

// Deallocation function (likely operator delete)
extern void FUN_009c8eb0(void* ptr);

class PooledObject {
public:
    // +0x00: virtual function table pointer
    void* vtable;
    // +0x04: pointer to a memory block (part of pool or allocated raw memory)
    int* memoryBlockPtr;
    // +0x08: additional pointer (cleared alongside memoryBlockPtr, possibly next/prev)
    int* auxiliaryPtr;

    // Destructor (returns the object back to the memory pool)
    // flags: if bit 0 is set, calls deallocation function (e.g., operator delete)
    void __thiscall destructor(unsigned char flags) {
        // Set vtable to base class vtable (destructor stage)
        this->vtable = &PTR_FUN_00e37110;

        // If a memory block is attached, return it to the free list
        if (this->memoryBlockPtr != 0) {
            // Get the global free list cursor pointer (double indirection)
            int** ppCursor = (int**)(DAT_01206880 + 0x14);
            // Write sentinel pointer at current cursor position
            *(void**)(*ppCursor) = &PTR_LAB_01123be8;
            // Advance cursor by 4 bytes
            (*ppCursor) = (int*)((uint8_t*)(*ppCursor) + 4);
            // Write the freed memory block pointer
            *(int*)(*ppCursor) = (int)this->memoryBlockPtr;
            // Advance cursor by another 4 bytes
            (*ppCursor) = (int*)((uint8_t*)(*ppCursor) + 4);

            // Clear the pointers
            this->memoryBlockPtr = 0;
            this->auxiliaryPtr = 0;
        }

        // Optionally deallocate the object itself
        if (flags & 1) {
            FUN_009c8eb0(this);
        }
    }
};