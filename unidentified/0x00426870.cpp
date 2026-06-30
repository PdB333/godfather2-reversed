// FUN_00426870: SomeClass::constructor

#include <cstddef>

// Assembly-level constructor for SomeClass.
// Called with a flag byte in param_2. If bit 0 is set, calls a deallocation function (likely operator delete) on the object after base initialization.
// This pattern suggests either a placement-new constructor with optional cleanup, or a custom allocation scheme.
// The base initialization (FUN_00426890) sets up the object's fields.

class SomeClass {
public:
    void* __thiscall constructor(unsigned char flags);
    // Base initialization, likely virtual or base class constructor.
    void __thiscall baseInit();
    // Deallocation function, probably operator delete or a custom free.
    static void __cdecl deallocate(void* ptr);
};

// 0x00426870
void* __thiscall SomeClass::constructor(unsigned char flags) {
    // Call base initialization (e.g., base class constructor or field setup).
    baseInit();

    // If the low bit of flags is set, deallocate the object's memory.
    // This is used when the constructor needs to free itself (e.g., if the allocation was external or if error handling is needed).
    if (flags & 1) {
        deallocate(this);
    }

    // Return the constructed object pointer (this).
    return this;
}