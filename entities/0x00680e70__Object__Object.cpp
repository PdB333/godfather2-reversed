// FUNC_NAME: Object::Object
// Address: 0x00680e70
// Constructor for base Object class. Sets vtable at offset 0x20 (second vtable for interface?),
// clears global static flag, and optionally calls cleanup function if flag bit 0 is set.
// Possibly part of EARS::Framework::Object or similar.

#include <cstdint>

// Forward declarations of internal functions called.
extern void FUN_007edfb0();                // Likely engine initialization routine
extern void FUN_009c8eb0(void* ptr);       // Likely cleanup/deallocation routine

// Global static flag (probably for singleton or first-time init)
static int32_t g_objectInitFlag = 0;      // DAT_0112995c

// Vtable symbol (for offset 0x20)
extern void* vtablePtr_0x20;             // PTR_LAB_00d580f8

class Object {
public:
    // Constructor
    // param_1 (this): pointer to memory for object (may be 0 if null pointer? But then function returns 0)
    // param_2 (flags): bit0 - if set, calls cleanup on this
    static __thiscall Object* createObject(void* mem, uint8_t flags); // This actually is the constructor itself
};

// Implementation (as given)
__thiscall int __fastcall Object::createObject(void* param_1, uint8_t param_2) {
    void** vtableSlot;

    // Determine where to store the vtable pointer (offset +0x20)
    if (param_1 == nullptr) {
        vtableSlot = nullptr;
    } else {
        vtableSlot = reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(param_1) + 0x20); // +0x20
    }

    // Set vtable pointer at that offset
    *vtableSlot = &vtablePtr_0x20;

    // Clear global flag
    g_objectInitFlag = 0;

    // Call general initialization routine
    FUN_007edfb0();

    // If bit 0 of flags is set, call cleanup/destruction (??) on self
    if ((param_2 & 1) != 0) {
        FUN_009c8eb0(param_1);
    }

    // Return pointer to the object (or null if input was null)
    return reinterpret_cast<int>(param_1);
}