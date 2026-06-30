// FUNC_NAME: Entity::testFlag
// Address: 0x00724dc0
// Role: Tests if a specific flag is set on the entity, using a virtual method to retrieve the flag state.
// Returns the flag mask if set, otherwise 0.

uint __thiscall Entity::testFlag(Entity *this, uint flagMask)
{
    int result;
    char flagSet;

    result = 0;
    // Virtual method at vtable+0x10: likely returns a boolean or byte indicating flag state.
    // Signature: char (__thiscall*)(Entity*, uint, int*)
    flagSet = ((char (__thiscall*)(Entity*, uint, int*))this->vtable[0x10])(this, flagMask, &result);
    return (flagSet != '\0') ? flagMask : 0;
}