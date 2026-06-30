// FUNC_NAME: SomeClass::constructorWithFlag
undefined4 __thiscall SomeClass::constructorWithFlag(SomeClass* this, uint8_t flag)
{
    // Call the base (main) constructor
    SomeClass::baseConstructor(this);

    // If the flag's lowest bit is set, perform additional initialization (e.g., register with manager)
    if ((flag & 1) != 0) {
        SomeClass::registerWithManager(this);
    }

    return this;
}