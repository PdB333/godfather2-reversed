// 004cac00: EARSAllocator::allocateNode

#include <cstdint>

// Structure allocated by this function (size 0x18)
struct AllocNode {
    uint32_t field0;   // +0x00
    uint32_t field4;   // +0x04
    uint32_t field8;   // +0x08
    uint32_t fieldC;   // +0x0C (maybe)
    uint32_t field10;  // +0x10 (maybe)
    uint8_t  field14;  // +0x14
    uint8_t  field15;  // +0x15
    // padding to 0x18
};
static_assert(sizeof(AllocNode) == 0x18, "Unexpected size");

class EARSAllocator {
public:
    void* allocateNode(); // this: ecx
private:
    // Memory layout:
    // +0x00: vtable pointer (maybe)
    // +0x04: pointer to function table (vtable for allocation)?
    // +0x08: fallback buffer pointer (nullable)
};

// Allocation function type: __fastcall, first arg edx=size, second arg ecx? Actually in decompiled it's called with two args: size and a pointer (fallback).
// The calling convention in decompiled is __fastcall with param_1 as implicit this? Actually it's __fastcall, but the first two args are in ECX and EDX typically.
// Ghidra's __fastcall with one parameter means it's a thiscall (ECX = this). The function call inside uses a function pointer from vtable, so we'll treat it as a regular function call.
typedef void* (__fastcall *AllocFunc)(void* this, uint32_t size, void* fallback); // this is the function table?

void* EARSAllocator::allocateNode() {
    // Get fallback pointer from offset 0x08
    void* fallback = *(void**)((uint8_t*)this + 8);
    uint32_t localFallback[3] = {0, 0, 0}; // temporary fallback if null

    // If fallback is null, use local zeros as placeholder (to avoid null pointer to allocator)
    void* bufferPtr;
    if (fallback != nullptr) {
        bufferPtr = fallback;
    } else {
        bufferPtr = localFallback; // points to local array
    }

    // Retrieve function pointer from vtable at this+4
    // The vtable is a pointer to a pointer to function: *(uint32_t*)(this+4) points to a table, first entry is the function.
    uint32_t* funcTable = *(uint32_t**)((uint8_t*)this + 4);
    AllocFunc allocFunc = (AllocFunc)(*funcTable); // first virtual function

    // Call allocation function: size 0x18, and the buffer pointer (as a hint or fallback)
    void* result = allocFunc(nullptr, 0x18, bufferPtr); // the 'this' of allocFunc is unknown, pass nullptr.

    // Initialize allocated block (size 0x18)
    if (result != nullptr) {
        ((uint32_t*)result)[0] = 0; // field0
        // Check for null is redundant but from decompiled:
        if ((uint32_t*)result + 1 != nullptr) {
            ((uint32_t*)result)[1] = 0; // field4
        }
        if ((uint32_t*)result + 2 != nullptr) {
            ((uint32_t*)result)[2] = 0; // field8
        }
        *(uint8_t*)((uint8_t*)result + 0x15) = 0; // field15
        *(uint8_t*)((uint8_t*)result + 0x14) = 1; // field14 = 1
    }

    return result;
}