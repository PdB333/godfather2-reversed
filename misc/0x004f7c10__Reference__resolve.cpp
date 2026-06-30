// FUNC_NAME: Reference::resolve
// Function address: 0x004f7c10
// Role: Resolves an object reference. If any of the 4 direct pointers (offsets 0x38-0x44) are non-null,
//       calls a validation function with the first pointer and a type ID (offset 0x04). On success returns that pointer.
//       Otherwise computes a pointer from a per-thread array: *(TLS slot 2) + 0x50 + offset at +0x10.

#include <cstdint>

// External function: verifies/resolves a reference given a type ID and a pointer candidate.
// Returns non-null pointer on success, null otherwise.
int* __cdecl validateReference(int typeId, int* ptr);

class Reference {
public:
    // __thiscall assumes 'this' is passed in ECX
    int* __fastcall resolve() {
        // Thread-local storage slot 2 (index 2, offset 8 from TLS array) holds a base pointer
        // FS:[0x2c] -> TLS array -> slot[2] -> base pointer
        int* tlsBase = *(int**)(*(int**)(__readfsdword(0x2c)) + 8); // +0x8 = slot 2 (each slot is 4 bytes)

        // Offsets from this
        int typeId = *(int*)((uintptr_t)this + 0x04); // +0x04: type/class identifier
        int index  = *(int*)((uintptr_t)this + 0x10); // +0x10: index into per-thread array (offset from base)
        int* ptr38 = *(int**)((uintptr_t)this + 0x38); // +0x38: primary pointer
        int* ptr3C = *(int**)((uintptr_t)this + 0x3C); // +0x3C
        int* ptr40 = *(int**)((uintptr_t)this + 0x40); // +0x40
        int* ptr44 = *(int**)((uintptr_t)this + 0x44); // +0x44

        // If any of the direct pointers is non-zero, attempt to validate the first one
        if (ptr38 != nullptr || ptr3C != nullptr || ptr40 != nullptr || ptr44 != nullptr) {
            int* result = validateReference(typeId, ptr38);
            if (result != nullptr) {
                return result;
            }
        }

        // Fallback: compute pointer from per-thread base + 0x50 + index
        // The base pointer points to a structure where +0x50 is the start of an array or table.
        return (int*)((uintptr_t)tlsBase + 0x50 + index);
    }
};