// FUNC_NAME: CSomeClass::constructor
// Reconstructed from 0x00652cb0 (likely a base class constructor with optional cleanup flag)
class CSomeClass {
public:
    // Constructor - takes a flags byte
    // Call to FUN_00652ea0 (likely base initialization or member setup)
    // If param_2 & 1, calls FUN_009c8eb0 (operator delete / destructor) on this
    void* __thiscall constructor(byte flags);
};

void* __thiscall CSomeClass::constructor(byte flags) {
    // Calls base/component initialization function
    FUN_00652ea0();

    // If flag indicates cleanup (e.g., placement new failure or conditional destruction)
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);  // Possibly operator delete or partial destructor
    }

    return this;
}