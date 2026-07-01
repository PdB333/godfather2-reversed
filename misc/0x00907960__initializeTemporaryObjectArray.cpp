// FUNC_NAME: initializeTemporaryObjectArray
// Address: 0x00907960
// Allocates a temporary array of 0x14-byte objects, constructs them, initializes using global counts, and frees the array.
// Likely part of engine startup to process static data.

#include <cstdint>

// Forward declarations for called functions (unknown purpose)
bool __cdecl FUN_00566920();                                 // return non-zero to proceed
void* __cdecl FUN_009c8e80(size_t size);                     // memory allocation
void* __cdecl FUN_00907d50(void* array, uint32_t count);     // first initialization
void __cdecl FUN_00906f90(void* someVal, uint32_t count);    // second initialization
void __cdecl FUN_00566000(void* array, uint32_t count, void* constructor, int zero); // register/destruct-related
void __cdecl FUN_009c8f10(void* ptr);                        // free or destruct array

// Constructor for objects (size 0x14 = 20 bytes)
void __thiscall LAB_00907620(void* thisPtr);

// Another function pointer used in registration
void LAB_00907660();

// Global counts
extern uint32_t DAT_00d82788;
extern uint32_t DAT_00d82d30;

int __cdecl FUN_00907960() {
    if (FUN_00566920() != 0) {
        uint32_t totalCount = DAT_00d82788 + DAT_00d82d30;   // combined count
        size_t allocSize = totalCount * 0x14;                // each object 20 bytes
        // Safer multiplication with overflow check (as in original assembly)
        // size_t allocSize = (size_t)((uint64_t)totalCount * 0x14);
        void* array = FUN_009c8e80(allocSize);
        if (array != nullptr) {
            // construct each element in-place
            __vector_constructor_iterator__(array, 0x14, totalCount, &LAB_00907620);
            void* result = FUN_00907d50(array, DAT_00d82d30);   // first init using second global
            FUN_00906f90(result, DAT_00d82788);                  // second init using first global
            FUN_00566000(array, totalCount, &LAB_00907660, 0);   // register/attach
            FUN_009c8f10(array);                                 // free array
        }
    }
    return 1;
}