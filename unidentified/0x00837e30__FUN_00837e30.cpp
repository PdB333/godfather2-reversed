// FUNC_NAME: SomeClass::SomeClass

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte initFlag)
{
    // Call base class constructor or object initializer
    initializeBase(this);
    
    // If the low bit of initFlag is set, perform additional initialization
    if ((initFlag & 1) != 0) {
        extraInitialization(this);
    }
    
    return this;
}