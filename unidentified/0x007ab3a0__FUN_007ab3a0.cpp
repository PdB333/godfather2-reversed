// FUNC_NAME: SomeClass::SomeClass
// Address: 0x007ab3a0
// Thin wrapper delegate sthat calls a common initialization routine at 0x007e0bd0.
// Likely a base class constructor stub.

void baseConstructor(void); // Forward declaration for the actual constructor at 0x007e0bd0

void __thiscall SomeClass::SomeClass(void) {
    baseConstructor(); // Delegates initialization to base class or common init
}