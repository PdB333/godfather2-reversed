// FUNC_NAME: UnknownClass::constructor
// Address: 0x008d0de0
// Reconstructed constructor with memory management flag.
// Sets three vtable pointers at offsets 0x00, 0x3C, and 0x48, then calls base constructor.
// If param_2 & 1 is set, frees the object (size 0x5c) after construction.
// This pattern is unusual; possibly an allocating constructor with cleanup on failure,
// or part of a custom memory scheme.

class UnknownBase1 { /* ... */ };
class UnknownBase2 { /* ... */ };
class UnknownBase3 { /* ... */ };

class UnknownClass : public UnknownBase1, public UnknownBase2, public UnknownBase3 {
public:
    // Constructor
    void* __thiscall UnknownClass::constructor(byte flag) {
        // Set vtable pointers for multiple inheritance
        *(void**)this = &PTR_FUN_00d7cf4c;          // +0x00: vtable for base1
        *(void**)((char*)this + 0x3C) = &PTR_LAB_00d7cf3c; // +0x3C: vtable for base2
        *(void**)((char*)this + 0x48) = &PTR_LAB_00d7cf38; // +0x48: vtable for base3

        // Call base class constructor(s)
        FUN_008d0210();

        // If flag bit 0 is set, deallocate this object (size 0x5c = 92 bytes)
        if (flag & 1) {
            FUN_0043b960(this, 0x5c); // operator delete or custom deallocation
        }

        return this;
    }

    virtual ~UnknownClass() {} // Required for vtable
};