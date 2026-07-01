// FUNC_NAME: Entity::testFlag
uint __thiscall Entity::testFlag(Entity *this, uint flagMask)
{
    // vtable+0x10: virtual function to check if a flag is active
    // Returns flagMask if the flag is set, else 0
    bool flagSet;
    int ignored;
    
    flagSet = (this->vtable[4])(flagMask, &ignored) != '\0';
    return flagSet ? flagMask : 0;
}