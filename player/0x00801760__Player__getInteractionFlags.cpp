// FUNC_NAME: Player::getInteractionFlags
uint __thiscall Player::getInteractionFlags(Player* thisPlayer, void* targetEntity)
{
    uint flags = 0;

    // Check virtual method at vtable+0x1f8 (likely isDead or isIncapacitated)
    bool isDead = (**(code (__thiscall**)(Player*))(*(uint*)thisPlayer + 0x1f8))(thisPlayer);
    if (isDead ||
        // Check health field at offset 0xFF8 (param_1[0x3fe])
        *(char*)((uint)thisPlayer + 0xFF8) > 0 ||
        // Check flag at offset 0x8E8, bit 17 (param_1[0x23a] >> 0x11 & 1)
        (*(uint*)((uint)thisPlayer + 0x8E8) >> 0x11 & 1) != 0)
    {
        flags |= 1; // Bit 0: can interact or is actionable
    }

    // Check virtual method at vtable+0x1fc (likely hasTarget or isFocused)
    bool hasTarget = (**(code (__thiscall**)(Player*))(*(uint*)thisPlayer + 0x1fc))(thisPlayer);
    if (hasTarget)
    {
        // Field at offset 0x1C78 (param_1[0x71e]) is a pointer to some sub-object
        void* subObject = *(void**)((uint)thisPlayer + 0x1C78);
        void* baseObject;
        if (subObject == nullptr)
        {
            baseObject = nullptr;
        }
        else
        {
            // Subtract 0x48 to get the containing structure (e.g., parent object)
            baseObject = (void*)((uint)subObject - 0x48);
        }
        if (baseObject != targetEntity)
        {
            flags |= 2; // Bit 1: target mismatch or different entity
        }
    }

    return flags;
}