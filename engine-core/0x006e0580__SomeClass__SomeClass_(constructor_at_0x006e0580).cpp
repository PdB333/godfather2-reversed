// FUNC_NAME: SomeClass::SomeClass (constructor at 0x006e0580)
// Reconstructed C++ for EA EARS engine object constructor. Sets up multiple vtables and initializes members.
// param1: this pointer (0x128 bytes total)
// param2: flag indicating allocation type (bit0: if set, calls destructor-like cleanup)

class SomeBase {
public:
    virtual ~SomeBase(); // +0x0 vtable
    // ... other members
};

class SomeInterface1 {
public:
    virtual ~SomeInterface1(); // vtable at offset +0x3C
};

class SomeInterface2 {
public:
    virtual ~SomeInterface2(); // vtable at offset +0x48
};

class SomeInterface3 {
public:
    virtual ~SomeInterface3(); // vtable at offset +0x50
};

class SomeClass : public SomeBase, public SomeInterface1, public SomeInterface2, public SomeInterface3 {
public:
    // Constructor: takes a flag (maybe "isHeapAllocated" or "destroyOnFailure")
    SomeClass(byte flag);
    virtual ~SomeClass();

    // Member at offset +0x68 (0x1a * 4) - possibly a pointer to another object
    void* field_0x68; // some pointer, checked for non-null and freed

private:
    void initBase(); // calls FUN_00473880, base initialization
    void freeMember(); // calls FUN_004daf90 on field_0x68
    void cleanup(); // calls FUN_0043b960 if flag set
};

SomeClass::SomeClass(byte flag) {
    // Set primary vtable (SomeBase)
    *(void**)this = &PTR_FUN_00d5f758; // vtable for SomeBase

    // Set secondary vtables for interfaces
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00d5f748; // SomeInterface1 vtable
    *(void**)((char*)this + 0x48) = &PTR_LAB_00d5f744; // SomeInterface2 vtable
    *(void**)((char*)this + 0x50) = &PTR_LAB_00d5f740; // SomeInterface3 vtable

    // Check if member at +0x68 is already allocated, if so free it
    if (field_0x68 != nullptr) {
        freeMember(); // FUN_004daf90(this + 0x68) - likely deletes or releases the member
    }

    // Call base class initialization routine
    initBase(); // FUN_00473880

    // If flag bit 0 is set, perform cleanup/destruction depending on allocation
    // This may be a custom memory management pattern (e.g., placement new with delete flag)
    if (flag & 1) {
        cleanup(); // FUN_0043b960(this, 0x128) - likely frees memory or calls destructor
    }
}