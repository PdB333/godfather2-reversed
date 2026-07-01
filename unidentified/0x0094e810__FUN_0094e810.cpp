// FUNC_NAME: UnknownClass::constructor
// Address: 0x0094e810 - Initializes a new instance (likely related to input or controller system)
// Calls base init (FUN_0046c590) then sets vtable and member fields.

// Known offsets:
// +0x00: vtable pointer
// +0x3C: pointer (ptr1)
// +0x48: pointer (ptr2)
// +0x50: int (int1)
// +0x54: short (short1)
// +0x56: short (short2)
// +0x58: int (int2)
// +0x5C: short (short3)
// +0x5E: short (short4)

#include <cstdint>

typedef void (*BaseInitFunc)(uint32_t param);
extern BaseInitFunc baseClassInit; // actually FUN_0046c590

class UnknownClass {
public:
    void** vtable;      // +0x00
    void*  ptr1;        // +0x3C
    void*  ptr2;        // +0x48
    int32_t int1;       // +0x50
    int16_t short1;     // +0x54
    int16_t short2;     // +0x56
    int32_t int2;       // +0x58
    int16_t short3;     // +0x5C
    int16_t short4;     // +0x5E

    __thiscall UnknownClass(uint32_t param) {
        // Call base class initialization
        baseClassInit(param);

        // Set vtable pointer for this class
        vtable = (void**)0x00d8ba60; // PTR_FUN_00d8ba60

        // Initialize member fields
        ptr1 = (void*)0x00d8ba50;  // PTR_LAB_00d8ba50
        ptr2 = (void*)0x00d8ba4c;  // PTR_LAB_00d8ba4c
        int1 = 0;
        short1 = 0;
        short2 = 0;
        int2 = 0;
        short3 = 0;
        short4 = 0;
    }
};