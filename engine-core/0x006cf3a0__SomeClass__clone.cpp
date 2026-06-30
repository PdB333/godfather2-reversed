// FUNC_NAME: SomeClass::clone
// Function at 0x006cf3a0: Clones an object, allocating memory and copying matrix data from source+0x60 to two locations in the new object.

#include <cstdint>

// Structure for allocation parameters (size, alignment, flags)
struct AllocationParams {
    uint32_t size;      // +0x00
    uint32_t alignment; // +0x04
    uint32_t flags;     // +0x08
};

// Forward declarations for external functions
void* __fastcall getMemoryManager(); // FUN_009c8f80
void __fastcall initializePart(void* param_1); // FUN_00473950
void __fastcall initSomething(); // FUN_00473750
void __fastcall registerClone(uint32_t globalHandle); // FUN_00473b10

// Global variable (probably a handle or singleton pointer)
extern uint32_t _DAT_00d5f1e0;

// Virtual function table pointers (provided by linker)
extern void* PTR_FUN_00d5f1f0;  // vtable for SomeClass
extern void* PTR_LAB_00d5f1e8; // secondary vtable for multiple inheritance

// Class definition (partial)
class SomeClass {
public:
    // Virtual function table pointer at +0x00
    // Probably multiple inheritance, second vtable at +0x08
    // Data members:
    // +0x08: first copy of 16 dwords (64 bytes) from source+0x60
    // +0x18: second copy of 16 dwords (64 bytes) from source+0x60
    // +0x28: some field set to 0

    // Method: clone this object
    SomeClass* __fastcall clone(int source) { // source is actually 'this'? Actually param_1 is source object
        // Actually param_1 is passed in ECX, so it's the source object. 
        // The function returns a new allocated SomeClass*.
        uint32_t** allocator = (uint32_t**)getMemoryManager();
        AllocationParams allocParams;
        allocParams.size = 0xB0;       // 176 bytes
        allocParams.alignment = 0x10;  // 16-byte aligned
        allocParams.flags = 0;         // no flags

        // Allocate memory for new object
        SomeClass* newObj = (SomeClass*)(*(allocator[0]))(0xB0, &allocParams);

        if (newObj != nullptr) {
            initializePart(source); // Some initialization on source object? Or on new?

            // Set virtual function tables
            newObj->vtable = &PTR_FUN_00d5f1f0;       // primary vtable at +0x00
            *(void**)((char*)newObj + 8) = &PTR_LAB_00d5f1e8; // secondary vtable at +0x08

            initSomething(); // Additional initialization

            // Clear field at offset 0x28
            *(uint32_t*)((char*)newObj + 0x28) = 0;

            // Copy two arrays of 16 dwords from source+0x60 to newObj+0x18 and newObj+0x8
            // Both copies read from same source location (source+0x60)
            uint32_t* src = (uint32_t*)(source + 0x60);
            uint32_t* dst1 = (uint32_t*)((char*)newObj + 0x18);
            for (int i = 0; i < 0x10; i++) {
                *dst1++ = *src;
                src++;
            }

            // Reset source pointer (or it's a copy of the same data)
            src = (uint32_t*)(source + 0x60);
            uint32_t* dst2 = (uint32_t*)((char*)newObj + 0x8);
            for (int i = 0; i < 0x10; i++) {
                *dst2++ = *src;
                src++;
            }

            registerClone(_DAT_00d5f1e0); // Register the clone
        }

        return newObj;
    }
};