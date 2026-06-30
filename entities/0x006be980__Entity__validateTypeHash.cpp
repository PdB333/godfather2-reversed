// FUNC_NAME: Entity::validateTypeHash
uint __thiscall Entity::validateTypeHash(uint param_2)
{
    // in_EAX is assumed to be passed in the EAX register before this call.
    // It typically holds the result of a previous operation.
    uint uVar1 = in_EAX & 0xFFFFFF00;  // Keep only the high 24 bits.

    // Check if both component pointers at +0x14 and +0x18 are valid.
    if (*(int*)(this + 0x14) != 0 && *(int*)(this + 0x18) != 0)
    {
        // If the type signature at (+0x14)->+0x54 matches the expected constant (0x637B907)
        // and the hash at (+0x18)->+0x54 equals the supplied param_2,
        // then return the high 24 bits of the hash with the low byte set to 1 (indicating success).
        if (*(uint*)(*(int*)(this + 0x14) + 0x54) == 0x637B907 &&
            *(uint*)(*(int*)(this + 0x18) + 0x54) == param_2)
        {
            return (*(uint*)(*(int*)(this + 0x18) + 0x54) & 0xFFFFFF00) | 1;
        }
        // else fall through to return the original high bits.
    }
    return uVar1;
}