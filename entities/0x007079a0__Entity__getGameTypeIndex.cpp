// FUNC_NAME: Entity::getGameTypeIndex
int __fastcall Entity::getGameTypeIndex(Entity* thisPtr)
{
    // +0x214: gameType (stored with offset 0x48 for valid types, 0 = none, 0x48 = invalid)
    int type = *(int*)((int)thisPtr + 0x214);
    if (type != 0 && type != 0x48)
    {
        return type - 0x48; // Convert internal type to game type enum value
    }
    return 0; // Return "none" type if invalid or unset
}