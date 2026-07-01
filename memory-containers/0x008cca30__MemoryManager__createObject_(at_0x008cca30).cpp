// FUNC_NAME: MemoryManager::createObject (at 0x008cca30)
// This function appears to be a static factory method that allocates and constructs an object via a memory manager singleton.
// It uses a virtual allocation call from an allocator object, then calls the class constructor on the allocated memory.

#include <cstdint>

// Forward declarations for internal functions.
// The memory manager allocator is obtained via a static function.
class Allocator;
Allocator* MemoryManager_getAllocator();

// The constructor for the target class (size 0xA0 = 160 bytes).
// The second parameter (param) likely controls initialization behavior.
void SomeClass_constructor(void* obj, int param);

// The target class size.
const uint32_t kClassSize = 0xA0;

// Alloc flags: type=2, alignment=0x10, option=0.
struct AllocParams {
    int type;       // +0x00: allocation type (2)
    int alignment;  // +0x04: requested alignment (0x10)
    int option;     // +0x08: additional flag (0)
};

// Main factory function.
void* __cdecl MemoryManager_createObject() {
    Allocator* allocator = MemoryManager_getAllocator();
    if (!allocator) return nullptr;

    AllocParams params;            // local_c structure
    params.type = 2;
    params.alignment = 0x10;
    params.option = 0;

    // Call virtual Allocate on the allocator.
    // The allocator vtable entry at offset 0 is likely `allocate(size, params*)`.
    typedef void* (__thiscall* AllocFunc)(Allocator*, uint32_t, AllocParams*);
    AllocFunc allocFunc = *(AllocFunc*)allocator;
    void* newObj = allocFunc(allocator, kClassSize, &params);

    if (newObj) {
        // Call constructor on the fresh memory, passing the option value (0).
        SomeClass_constructor(newObj, params.option);
        return newObj;
    }
    return nullptr;
}