// FUNC_NAME: BaseGameObject::constructor
// Address: 0x006abef0
// Role: Constructor for a game object with multiple inheritance (two base classes) and a sub-object.

#include <cstddef>

class BaseGameObject {
public:
    // Vtable pointers (multiple inheritance)
    void** vtable;                         // +0x00: primary vtable
    // ... other members (size unknown, offset to next vtable)
    void** vtable2;                        // +0x3c: secondary base class vtable
    void** vtable3;                        // +0x48: tertiary base class vtable
    // Sub-object at offset +0x14
    char subObject[ /* size unknown */ ];  // +0x14

    // Constructor (__fastcall, this in ecx)
    void __fastcall constructor(void) {
        // Set vtable pointers for multiple inheritance
        vtable  = reinterpret_cast<void**>(&PTR_FUN_00d5da8c);  // primary vtable
        vtable2 = reinterpret_cast<void**>(&PTR_LAB_00d5da7c);  // secondary vtable
        vtable3 = reinterpret_cast<void**>(&PTR_LAB_00d5da78);  // tertiary vtable

        // Initialize internal sub-object at +0x14
        FUN_004086d0(&subObject);   // likely sub-object constructor
        FUN_00408310(&subObject);   // additional sub-object setup

        // Initialize global singleton (DAT_0120e93c)
        FUN_004086d0(&DAT_0120e93c);

        // Static initializer for the class
        FUN_0046c640();
    }
};