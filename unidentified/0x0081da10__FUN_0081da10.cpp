// FUNC_NAME: SomeClass::SomeClass

// Reconstructed constructor for an engine object.
// Function at 0x0081da10: __thiscall, returns this pointer (undefined4).
// Calls a base initializer (0081d8e0) then conditionally calls an extra initializer (009c8eb0)
// based on the low bit of the parameter (initFlags).

// Known classes in the codebase: many EARS/Godfather2 classes follow this pattern.
// If more context becomes available, rename this class accordingly.

class SomeClass {
public:
    // Constructor: takes a byte flag controlling extra initialization.
    // Returns this pointer (implicit for constructors).
    __thiscall SomeClass(byte initFlags) {
        // Base initialization (likely base class constructor or member setup)
        initBase(); // FUN_0081d8e0

        // If bit 0 is set, perform additional initialization
        if (initFlags & 1) {
            initExtra(this); // FUN_009c8eb0
        }
    }

private:
    // Helper: base initialization called first
    void __thiscall initBase();   // No known parameters beyond this

    // Helper: extra initialization (called with 'this' as argument)
    void __thiscall initExtra();  // Implicitly receives this pointer
};