// FUNC_NAME: GenericClass::GenericClass
// Address: 0x00694a80
// This appears to be a constructor that delegates to base class initialization at 0x006940f0.
// The function takes the 'this' pointer (fastcall param_1) and returns it after calling the base init.

class GenericClass {
public:
    GenericClass();
    void baseInit(); // refers to function at 0x006940f0 (likely base class constructor or init)
};

__thiscall GenericClass::GenericClass() {
    this->baseInit();
    // return this (implied by calling convention)
}