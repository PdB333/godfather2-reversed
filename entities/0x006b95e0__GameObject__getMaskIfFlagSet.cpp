// FUNC_NAME: GameObject::getMaskIfFlagSet
uint __thiscall GameObject::getMaskIfFlagSet(GameObject *this, uint flagMask)
{
    bool unused;
    // Call virtual function at vtable+0x10 (index 4) to test flagMask validity
    // Returns non-zero if the flag is set / condition holds
    char isSet = (this->vtable[4])(this, flagMask, &unused);
    // If condition is true, return the original mask; otherwise return 0
    return (isSet != 0) ? flagMask : 0;
}