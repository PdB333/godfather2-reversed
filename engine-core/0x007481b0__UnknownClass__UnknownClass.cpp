// FUNC_NAME: UnknownClass::UnknownClass
// Function address: 0x007481b0
// Identified role: Constructor with conditional initialization flag.
// Calls base constructor (0x00747c50) and conditionally calls extra function (0x00624da0)
// based on lowest bit of param_2.

// Reconstructed C++ based on Ghidra decompilation.
// The flag (param_2) bit 0 triggers a call to a second member function (likely destructor or additional init).

class UnknownClass {
public:
    // Constructor takes a byte flag (often used for placement new or allocation tracking)
    UnknownClass(byte flag);
};

UnknownClass::UnknownClass(byte flag) {
    // Call base class constructor (likely __thiscall on this, no explicit this needed in C++ call)
    // Base constructor at 0x00747c50
    baseConstructor(); // renamed from FUN_00747c50; could be BaseClass::BaseClass()

    // If the flag's lowest bit is set, call an extra function on this object
    if (flag & 1) {
        // Extra function at 0x00624da0, takes 'this' as argument (likely a destructor or cleanup)
        extraFunction(this); // renamed from FUN_00624da0
    }
    // Constructor returns 'this' implicitly
}