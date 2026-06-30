// FUNC_NAME: get_object_id
// Function address: 0x005f37b0
// Role: Retrieves a 32-bit identifier from a nested object structure.
//       Returns 0xFFFFFFFF (invalid) if any pointer in the chain is null.

// Reconstructed C++ for internal game utility.
// The calling convention is __fastcall (this in ecx on x86).
// Offsets:
//   +0x2c: pointer to a pointer to an inner structure
//   inner structure +0x18: uint32 identifier

#include <cstdint>

uint32_t __fastcall get_object_id(void* self) {
    // Default invalid value
    uint32_t result = 0xFFFFFFFF;

    // Check if the root object exists
    if (self != nullptr) {
        // Dereference the pointer at offset 0x2c
        void** ppInner = *(void***)((uint8_t*)self + 0x2c);
        if (ppInner != nullptr) {
            // Dereference again to get the inner object
            void* pInner = *ppInner;
            if (pInner != nullptr) {
                // Read the 32-bit value at offset 0x18 inside the inner object
                result = *(uint32_t*)((uint8_t*)pInner + 0x18);
            }
        }
    }

    return result;
}