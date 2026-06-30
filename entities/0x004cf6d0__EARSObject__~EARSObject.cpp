// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x004cf6d0
// Role: Scalar deleting destructor. Calls base cleanup and optionally deallocates via vtable.

#include <cstdint>

// Global engine singleton (0x01223410)
extern void* gEngineBase;

// Offset to the deletion vtable table (offset +0x2D4 from gEngineBase)
const int kDeleterTableOffset = 0x2D4;

// Base class cleanup function (called unconditionally, likely destructor logic at 0x004cf700)
extern void __thiscall baseClassCleanup(void* thisPtr);

void* __thiscall EARSObject::~EARSObject(uint8_t flag) {
    // Execute base class destructor / common cleanup
    baseClassCleanup(this);

    // If flag bit 0 is set, call the vtable-based deallocation function (index 1, offset 4)
    if (flag & 1) {
        // Retrieve vtable from global engine state
        void* vtable = *(void**)((char*)gEngineBase + kDeleterTableOffset);
        // Function pointer at vtable[1] (offset 4) is the delete routine
        void (*deleter)(void*, int) = *(void (**)(void*, int))((char*)vtable + 4);
        deleter(this, 0);
    }

    return this;
}