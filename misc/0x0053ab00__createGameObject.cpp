// FUNC_NAME: createGameObject
// Address: 0x0053ab00
// Purpose: Allocates a game object (size 0xD0 = 208 bytes) using a memory manager singleton,
// then initializes it via a constructor call, checking for an error flag at offset +0x04.
// On allocation failure or error flag, returns nullptr.

// Note: This is likely a stateless factory function (static method of an unknown class).
// The memory manager obtained from FUN_009c8f80 uses vtable[0] as an allocation method
// taking (size, flags_struct_ptr). The allocation flags structure holds alignment (0x10) and other fields.
// The constructor FUN_005195b0 is called with (0, ?, param2, param3) – the second argument
// is the unaff_retaddr which might be a compiler-inserted this pointer or return address.
// Finally, the created object's flag byte at +0x04 is tested; if bit0 is set, vtable[0]
// (likely a release/destructor method) is called with arg=1 and the object is discarded.

#include <cstdint>

// Forward declarations for called functions
extern "C" void* FUN_009c8f80();      // Returns pointer to memory manager singleton
extern "C" void* FUN_005195b0(uint32_t, void*, uint32_t, uint32_t); // Constructor/initializer

// Game object structure (partial, only known offsets)
struct GameObject {
    void** vtable;   // +0x00
    uint8_t flags;   // +0x04  (bit0 = error/failure indicator)
    // ... rest of 0xD0 bytes
};

// Allocation flags structure passed to memory manager's vtable[0]
struct AllocFlags {
    uint32_t unknownField1; // typically 2
    uint32_t alignment;     // typically 0x10 (16-byte alignment)
    uint32_t unknownField2; // typically 0
};

// Memory manager structure (first entry points to vtable)
struct MemoryManager {
    void** vtable;
    // ...
};

// Factory function
GameObject* __cdecl createGameObject(uint32_t param1, uint32_t param2, uint32_t param3) {
    MemoryManager* memMgr = (MemoryManager*)FUN_009c8f80();
    if (!memMgr) return nullptr;

    // Prepare allocation flags
    AllocFlags allocFlags;
    allocFlags.unknownField1 = 2;
    allocFlags.alignment = 0x10;
    allocFlags.unknownField2 = 0;

    // Call memory manager's allocation routine (vtable[0])
    typedef int (__thiscall* AllocateFunc)(MemoryManager*, uint32_t size, AllocFlags* flags);
    AllocateFunc alloc = (AllocateFunc)(*(memMgr->vtable));
    int allocResult = alloc(memMgr, 0xD0, &allocFlags);

    GameObject* obj = nullptr;
    if (allocResult != 0) {
        // Memory allocated, call constructor
        // Note: second argument is unaff_retaddr (likely a hidden this or return address)
        obj = (GameObject*)FUN_005195b0(0, nullptr, param2, param3);
    } else {
        obj = nullptr;
    }

    // Check if construction flagged an error (bit0 at +0x04)
    if (obj) {
        if (obj->flags & 1) {
            // Error: release the object using vtable[0] method with argument 1
            typedef void (__thiscall* ReleaseFunc)(GameObject*, uint32_t arg);
            ReleaseFunc release = (ReleaseFunc)(*(obj->vtable));
            release(obj, 1);
            obj = nullptr;
        }
    }

    return obj;
}