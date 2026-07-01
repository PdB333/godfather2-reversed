// FUNC_NAME: UnknownClass::constructor (vtable setup with flag byte)
// Address: 0x009289c0
// Role: Constructor for an object with multiple virtual tables (multiple inheritance).
// Sets up vtables, calls cleanup on sub-objects, modifies vtable pointer, resets global, and optionally calls destructor if flag bit 0 set.

class UnknownClass {
public:
    // Constructor: param_2 = flag (bit0: delete on construction? or placement flag)
    void* constructor(byte flag) {
        // Set primary vtable
        *(void**)this = &PTR_FUN_00d87b98;               // +0x00: vtable for primary base
        *(void**)((int)this + 0x10) = &PTR_LAB_00d87b70; // +0x10: vtable for second base
        *(void**)((int)this + 0x4C) = &PTR_LAB_00d87b6c; // +0x4C: vtable for third base

        // Call cleanup/destructor on sub-objects at offsets 0x6C and 0x68
        // (FUN_009c8f10 is likely a destructor or release function)
        FUN_009c8f10(*(void**)((int)this + 0x6C)); // sub-object at +0x6C
        FUN_009c8f10(*(void**)((int)this + 0x68)); // sub-object at +0x68

        // Update vtable at +0x4C to a different pointer
        *(void**)((int)this + 0x4C) = &PTR_LAB_00d87b68; // new vtable

        // Reset global variable
        DAT_0112a87c = 0;

        // Call some initialization function
        FUN_005c16e0();

        // If flag bit 0 is set, call destructor (FUN_005c4480 likely operator delete or finalization)
        if (flag & 1) {
            FUN_005c4480(this);
        }

        return this;
    }
};

// Hypothetical class member offsets:
// +0x00: pointer to vtable (primary)
// +0x10: pointer to secondary vtable
// +0x4C: pointer to tertiary vtable (changed during construction)
// +0x68, +0x6C: pointers to sub-objects that are cleaned up
// Global DAT_0112a87c: some state flag