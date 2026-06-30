// FUNC_NAME: UnknownClass::constructor
undefined4 __thiscall UnknownClass::constructor(UnknownClass* this, byte flags)
{
    // Call the base class constructor or initializer
    baseConstructor();

    // If the lowest bit of the flags is set, call an additional initialization routine
    if ((flags & 1) != 0) {
        additionalInit(this);
    }

    return this;
}