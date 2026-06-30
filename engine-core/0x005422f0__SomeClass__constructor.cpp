// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(byte initFlag) {
    // Call base class constructor / initialization routine
    this->baseConstructor();

    // If the lowest bit of initFlag is set, perform additional initialization
    if ((initFlag & 1) != 0) {
        this->additionalInit();
    }

    return this;
}