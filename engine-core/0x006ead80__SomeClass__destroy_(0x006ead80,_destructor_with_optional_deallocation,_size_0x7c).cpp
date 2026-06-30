// FUNC_NAME: SomeClass::destroy (0x006ead80, destructor with optional deallocation, size 0x7c)
// This function appears to be a destructor that conditionally deallocates memory.
// It calls a base class method at 0x006eab20 (likely base destructor/cleanup),
// then if param_2 (bit 0) is set, calls sized operator delete at 0x0043b960 with size 0x7c (124 bytes).
// Returning this after deletion is unusual – may be a custom framework pattern.

class SomeBaseClass {
public:
    void __thiscall baseCleanup(); // FUN_006eab20
};

class SomeClass : public SomeBaseClass {
public:
    // Parameter: deallocateMemory - if true, call sized operator delete after base cleanup
    // Returns the original this pointer (possibly for chaining or framework usage)
    void* __thiscall destroy(bool deallocateMemory) {
        // Call base class cleanup/destructor
        baseCleanup();

        // Conditionally deallocate the object's memory
        if (deallocateMemory) {
            // Sized operator delete – likely a custom allocator, size = 0x7c (124 bytes)
            // FUN_0043b960 is the sized delete function
            operator delete(this, sizeof(*this));
        }

        return this; // Return this pointer (may be used by a parent allocator)
    }
};