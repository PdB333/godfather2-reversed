// FUNC_NAME: EARSObject::getFlagMaskIfSet
uint __thiscall EARSObject::getFlagMaskIfSet(int* this, uint mask)
{
    // +0x10: vtable slot 4 (index 4) - virtual function that tests if a given flag mask is set.
    // Returns non-zero (true) if the flag is set, zero otherwise.
    char isSet;
    uint dummy = 0; // unused output parameter, required by the virtual function signature
    isSet = (**(code (__thiscall**)(int*, uint*))(*this + 0x10))(mask, &dummy);
    // If the flag is set, return the original mask; otherwise return 0.
    // This is done via bitwise trick: -(uint)(isSet != 0) produces 0xFFFFFFFF if true, else 0.
    return -(uint)(isSet != '\0') & mask;
}