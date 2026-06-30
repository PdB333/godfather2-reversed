// FUNC_NAME: SomeClass::SomeClass
// Address: 0x00705ed0
// Role: Constructor for SomeClass. Calls base constructor unconditionally, then conditionally calls a sub-constructor if flag's bit 0 is set.

SomeClass::SomeClass(uint8_t flag) {
    // Base initialization (likely vtable/base class setup)
    this->baseConstructor();
    if (flag & 1) {
        // Optional sub-initialization (possibly allocation or additional member setup)
        this->subConstructor();
    }
    // Object pointer (this) is returned per __thiscall convention.
}