// FUNC_NAME: UnknownClass::checkTypeAndCreateInstance
// Address: 0x007675b0
// This function appears to be a type-checked factory or initializer.
// It retrieves a class ID from the object's vtable and compares it to a magic constant 0x27a0f69c.
// If it matches, it calls two helper functions to initialize some internal data structures.
// Otherwise, it calls an error handler (likely cleanup or a different creation path).
//
// The global _DAT_00d64c8c is likely a manager or resource holder.

#include <cstdint>

// Forward declarations of callees
void __cdecl FUN_0073e4d0(void* obj);            // Error/cleanup handler for non-matching type
void __cdecl FUN_0071add0(uint8_t* bufOut, uint8_t* bufIn);  // Initialize buffers (maybe RTTI/class info)
void __cdecl FUN_00755410(uint8_t* buf1, uint8_t* buf2, int32_t flag, void* globalData, int32_t anotherFlag); // Create/finalize object

extern void* _DAT_00d64c8c; // Global pointer, likely to a manager singleton

class BaseWithRTTI {
public:
    virtual uint32_t getClassID() const; // First vtable function, returns a type identifier
};

// __thiscall reconstruction: this pointer is the first parameter (param_1)
void __thiscall checkTypeAndCreateInstance(void* thisPtr) {
    BaseWithRTTI* obj = reinterpret_cast<BaseWithRTTI*>(thisPtr);
    uint32_t classID = obj->getClassID(); // (**(code **)*param_1)();
    
    if (classID != 0x27a0f69c) {
        // Type mismatch – call the general handler
        FUN_0073e4d0(thisPtr);
        return;
    }
    
    // Type matches – construct temporary buffers and initialize
    uint8_t buffer1[12]; // auStack_18 (12 bytes)
    uint8_t buffer2[12]; // auStack_c  (12 bytes)
    
    FUN_0071add0(buffer2, buffer1);  // Note: order as in decompiled (param1 = auStack_c, param2 = auStack_18)
    FUN_00755410(buffer2, buffer1, 0, _DAT_00d64c8c, 0);
}