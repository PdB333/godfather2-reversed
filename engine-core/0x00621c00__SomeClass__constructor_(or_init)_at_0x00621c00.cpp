// FUNC_NAME: SomeClass::constructor (or init) at 0x00621c00
// Role: Constructor that calls initialization function and returns this pointer.
// This is a __fastcall function with ECX = this pointer.

class SomeClass {
public:
    // Constructor: calls internal initialization and returns this.
    __fastcall SomeClass() {
        // Call initialization function (likely base class constructor or member init)
        FUN_00622570(); // Placeholder for actual initialization
        return this;
    }
};