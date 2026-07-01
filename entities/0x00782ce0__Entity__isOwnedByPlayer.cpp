// FUNC_NAME: Entity::isOwnedByPlayer
bool __thiscall Entity::isOwnedByPlayer(void* thisPtr)
{
    // Check if the entity's owner (at +0x28) matches the global player reference
    char result;
    result = FUN_0043c6c0(*(uint32_t*)((char*)thisPtr + 0x28), DAT_00e52468);
    return result != 0;
}