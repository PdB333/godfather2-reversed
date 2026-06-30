// FUNC_NAME: EARSBase::constructor
// Function address: 0x004f11d0
// Role: Base constructor for EARS engine objects. Initializes base state, 
//       and conditionally performs additional cleanup or finalization if 
//       the low bit of param_2 is set.
// Calling convention: __thiscall (this in ecx)

#include <cstdint>

class EARSBase {
public:
    // Constructor – returns 'this' after initialization.
    // param_2: flag byte; if bit 0 is set, calls an internal cleanup method.
    EARSBase* __thiscall constructor(uint8_t flag) {
        // Initialize base class members (FUN_004f0e80)
        baseInitialize();

        // If flag indicates finalization, perform additional cleanup (FUN_009c8eb0)
        if ((flag & 1) != 0) {
            destructorBody(this);
        }

        return this;
    }

private:
    // Base initialization routine (no arguments)
    void __thiscall baseInitialize();   // 0x004f0e80

    // Internal cleanup/destructor body that operates on the object (FUN_009c8eb0)
    void __thiscall destructorBody(EARSBase* obj); // 0x009c8eb0
};