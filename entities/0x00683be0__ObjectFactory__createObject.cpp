// FUNC_NAME: ObjectFactory::createObject
// Address: 0x00683be0
// This function allocates an object of size 0xF0 (240 bytes) using the game's memory allocator,
// then initializes it via an initialization function. Returns a pointer to the initialized object,
// or 0 on allocation failure.

#include <cstdint>

class ObjectFactory {
public:
    // param_1: likely an allocator context or a pointer to the object to initialize
    // param_2: additional parameter passed to the allocator (e.g., heap index or flags)
    static void* __thiscall createObject(void* param_1, uint32_t param_2) {
        // Allocation parameters:
        // local_c = 2 (maybe heap type: 2 = gameplay heap)
        // local_8 = 0x10 (alignment, e.g., 16 bytes)
        // local_4 = 0 (flags)
        struct AllocParams {
            uint32_t heapType;   // +0x00
            uint32_t alignment;  // +0x04
            uint32_t flags;      // +0x08
        } allocParams;
        allocParams.heapType = 2;
        allocParams.alignment = 0x10;
        allocParams.flags = 0;

        // FUN_0043b980: memory allocation function
        // signature: int __cdecl allocate(uint32_t size, AllocParams* params, uint32_t context)
        // Returns non-zero on success (the allocated pointer? or just success code?)
        int allocResult = FUN_0043b980(0xF0, &allocParams, param_2);
        if (allocResult != 0) {
            // FUN_008119f0: initialization function for the object
            // param_1 is likely the object pointer (or allocator?)
            void* obj = FUN_008119f0(param_1);
            return obj;
        }
        return nullptr;
    }
};