// FUNC_NAME: SomeClass::Constructor
undefined4 * __thiscall SomeClass::constructor(SomeClass *this, byte allocFlag)
{
    this->vtable = &PTR_FUN_00d7cc20;
    baseConstructor(); // likely calls parent class constructor
    if ((allocFlag & 1) != 0) {
        conditionalCleanup(this); // probably deallocation or registration
    }
    return this;
}