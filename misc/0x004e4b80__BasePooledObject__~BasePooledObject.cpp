// FUNC_NAME: BasePooledObject::~BasePooledObject

// Destructor for BasePooledObject. Returns internal buffer to pool and optionally deletes this.
// param_2: bit 0 set means delete this object (call operator delete).
// Field offsets: +0x00 vtable, +0x10 iVar1 (pointer to pooled buffer), +0x14 (unused, zeroed).
// Global PoolAllocator at DAT_01206880; free list head at offset +0x14.

#include <cstdint>

// Global pool allocator structure
struct PoolAllocator {
    uint8_t pad_0x00[20];                  // +0x00: unknown
    void** freeListHead;                    // +0x14: pointer to current top of free stack
};
extern PoolAllocator g_poolAllocator;       // DAT_01206880

// Sentinel value marking free slot entries
static const void* FREE_SENTINEL = reinterpret_cast<const void*>(0x01123be8); // PTR_LAB_01123be8

// Provided by linker, frees object memory
extern void __cdecl operatorDelete(void* ptr); // FUN_009c8eb0

// Vtable for this class after destruction (base vtable)
extern void* g_vtable_BasePooledObject;     // PTR_FUN_00e37110

class BasePooledObject {
public:
    void* vtable;           // +0x00
    // ... other fields ...
    void* poolBuffer;       // +0x10 (param_1[4])
    void* unusedField;      // +0x14 (param_1[5])

    __thiscall ~BasePooledObject(uint8_t deleteFlag) {
        vtable = &g_vtable_BasePooledObject;

        if (poolBuffer != nullptr) {
            // Return buffer to global pool allocator's free list
            void** headPtr = reinterpret_cast<void**>(&g_poolAllocator.freeListHead);
            void* currentTop = *headPtr;

            // Push sentinel and then the buffer pointer onto free stack
            *reinterpret_cast<void**>(currentTop) = const_cast<void*>(FREE_SENTINEL);
            currentTop = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(currentTop) + sizeof(void*));
            *reinterpret_cast<void**>(currentTop) = poolBuffer;
            currentTop = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(currentTop) + sizeof(void*));

            // Update free list head
            *headPtr = currentTop;

            // Clear members
            poolBuffer = nullptr;
            unusedField = nullptr;
        }

        if (deleteFlag & 1) {
            operatorDelete(this);
        }
    }
};