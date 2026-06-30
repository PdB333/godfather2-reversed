// FUNC_NAME: EARSObject::getPointer
// Function at 0x004353d0 - Null-safe accessor for internal pointer/handle
// Delegates to 0x004dafd0 after checking 'this' (param_1)

unsigned int __thiscall EARSObject::getPointer()
{
    if (this == (void*)0)
        return 0;
    return ((unsigned int (__thiscall*)(EARSObject*))0x004dafd0)(this); // actual internal getter
}