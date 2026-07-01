// FUNC_NAME: UnknownClass::UnknownClass
// Function address: 0x00941390
// Role: Constructor for an unknown class with vtable at 0x00d8b334.
// The second parameter (flag) controls whether to call a cleanup/destructor function.

class UnknownClass {
public:
    void* vtable; // +0x00

    // Constructor
    UnknownClass* __thiscall UnknownClass(byte flag) {
        // Set vtable pointer
        this->vtable = (void*)0x00d8b334; // Vtable for UnknownClass
        // Call base class constructor (likely a global function)
        baseClassConstructor(); // FUN_004de130
        // If flag bit 0 is set, call destructor/cleanup
        if (flag & 1) {
            destructor(this); // FUN_009c8eb0
        }
        return this;
    }
};