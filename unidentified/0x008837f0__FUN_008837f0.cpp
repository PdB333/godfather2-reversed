// FUNC_NAME: SomeClass::SomeClass
int __thiscall SomeClass::SomeClass(byte flags) {
    // Call base class constructor (address 0x00883570)
    this->baseInit();

    // If the lowest bit of flags is set, perform additional initialization (address 0x00624DA0)
    if (flags & 1) {
        this->extraInit(); // +0x4? optional setup
    }

    return reinterpret_cast<int>(this);
}