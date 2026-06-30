// FUNC_NAME: SomeClass::SomeClass
void SomeClass::SomeClass() {
    // Delegate to base class initialization function (presumably constructor or init)
    // The this pointer is passed to the base init function at 0x00719b60
    BaseInitialize(this);
    return;
}