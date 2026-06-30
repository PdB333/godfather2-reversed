//FUNC_NAME: SomeClass::SomeClass

void __thiscall SomeClass::SomeClass(void* this, int arg1, int arg2, int arg3)
{
    // Call base class constructor at 0x00557e20
    BaseClassConstructor(this, arg1, arg2, arg3);
    // Call initialization function at 0x00c09cc0
    InitFunction(this, arg1, arg2, arg3);
}