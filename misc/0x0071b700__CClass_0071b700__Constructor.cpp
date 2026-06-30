// FUNC_NAME: CClass_0071b700::Constructor

#include <cstdint>

// Base class constructor at 0x008d8190 (likely initializes core fields and main vtable)
extern void __stdcall baseConstructor(void* secondaryParam);

// VTable pointers for this class (from data section)
extern void* const VTable_Main;       // PTR_FUN_00d61c28 at +0x00
extern void* const VTable_Secondary1; // PTR_LAB_00d61c18 at +0x3C
extern void* const VTable_Secondary2; // PTR_LAB_00d61c14 at +0x48
extern void* const VTable_Secondary3; // PTR_LAB_00d61c10 at +0x50
extern void* const VTable_Secondary4; // PTR_LAB_00d61bb0 at +0x54
extern void* const VTable_Secondary5; // PTR_LAB_00d61b48 at +0x58

class CClass_0071b700 {
public:
    void* vtable;                        // +0x00
    // ... other members between 0x04 and 0x3C ...
    void* vtable2;                       // +0x3C
    // ... possibly more members ...
    void* vtable3;                       // +0x48
    void* vtable4;                       // +0x50
    void* vtable5;                       // +0x54
    void* vtable6;                       // +0x58

    // Constructor
    void* __thiscall Constructor(void* param_2) {
        baseConstructor(param_2);            // base class construction
        this->vtable = &VTable_Main;         // set primary vtable
        this->vtable2 = &VTable_Secondary1;  // set secondary vtable at +0x3C
        this->vtable3 = &VTable_Secondary2;  // set secondary vtable at +0x48
        this->vtable4 = &VTable_Secondary3;  // set secondary vtable at +0x50
        this->vtable5 = &VTable_Secondary4;  // set secondary vtable at +0x54
        this->vtable6 = &VTable_Secondary5;  // set secondary vtable at +0x58
        return this;
    }
};