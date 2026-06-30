// FUNC_NAME: ObjectWithSubObjects::destroy
// Address: 0x00699480
// Role: Custom destructor that releases sub-objects via stored function pointers, then optionally frees the object.

#include <cstdint>

// Known deallocation function at 0x009c8eb0 (likely operator delete or custom free)
extern void __fastcall FUN_009c8eb0(void* ptr); // __fastcall for Microsoft convention, but actual may vary

class ObjectWithSubObjects {
    // Offsets relative to this (0x00)
    uint8_t pad_0x00[0x10];                 // +0x00: padding or other fields

    void* subObject1;                       // +0x10: pointer to first sub-object
    void (*releaseSubObject1)(void*);       // +0x1c: function to release/destroy subObject1

    void* subObject2;                       // +0x20: pointer to second sub-object
    void (*releaseSubObject2)(void*);       // +0x2c: function to release/destroy subObject2

public:
    // destroy - cleanup sub-objects and optionally free memory
    // param_2: flag byte; bit 0 set means deallocate this instance
    int __thiscall destroy(uint8_t deleteFlag) {
        // Release sub-object 2 (if present)
        if (subObject2 != nullptr) {
            releaseSubObject2(subObject2);
        }
        // Release sub-object 1 (if present)
        if (subObject1 != nullptr) {
            releaseSubObject1(subObject1);
        }
        // If requested, free this object's memory via the linked deallocator
        if (deleteFlag & 1) {
            FUN_009c8eb0(this);
        }
        return reinterpret_cast<int>(this);
    }
};