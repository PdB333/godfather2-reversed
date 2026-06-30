// FUNC_NAME: GodfatherObject::Constructor
// Function address: 0x005dbfb0
// Role: Constructor for a class with multiple vtable inheritance.
// Sets up base class vtable at +0x00 and secondary vtable at +0x10.
// Calls base class constructor via a function pointer stored in the secondary vtable (offset +0x04 of that vtable).
// Then calls own initialization functions and optionally frees the object if allocFlag indicates heap allocation.

class GodfatherObject {
public:
    // +0x00: vtable pointer for primary base class
    void** vtable;

    // +0x04: first data member (unknown)
    int field_04;

    // +0x08: second data member (unknown)
    int field_08;

    // +0x0C: third data member (unknown)
    int field_0C;

    // +0x10: vtable pointer for secondary base class
    void** secondaryVtable;

    // Constructor (MSVC style, returns this)
    __thiscall void* Constructor(byte allocFlag) {
        // Set primary vtable to base class's vtable
        this->vtable = (void**)&PTR_FUN_00e3f2e0;

        // Call base class constructor via a function pointer stored at offset 4 in the secondary vtable
        // (secondaryVtable points to the base class's vtable for the secondary base)
        void (*baseConstructor)() = *(void (__thiscall **)())((int)this->secondaryVtable + 4);
        baseConstructor();

        // Call initialization function (likely sets up some internal data)
        FUN_005de2f0();

        // Change secondary vtable pointer to its own vtable (for this class)
        this->secondaryVtable = (void**)&PTR_FUN_00e3f2e8;

        // Call another initialization function (possibly sets up fields or other bases)
        FUN_004de130();

        // Change primary vtable pointer to this class's final vtable
        this->vtable = (void**)&PTR_LAB_00e3f2e4;

        // Clear a global flag (maybe a singleton or init flag)
        DAT_01223508 = 0;

        // If the object was allocated on heap (allocFlag bit 0 set), call operator delete or similar
        if (allocFlag & 1) {
            FUN_009c8eb0(this);
        }

        return this;
    }
};

// Note: The actual function implementations (FUN_005de2f0, FUN_004de130, FUN_009c8eb0)
// and symbols (PTR_FUN_00e3f2e0, PTR_FUN_00e3f2e8, PTR_LAB_00e3f2e4) are not elaborated here.
// They correspond to internal routines and vtable addresses within the binary.