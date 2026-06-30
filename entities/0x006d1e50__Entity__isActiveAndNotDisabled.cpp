// FUNC_NAME: Entity::isActiveAndNotDisabled
bool Entity::isActiveAndNotDisabled(uint entityHandle)
{
    Entity* entity = (Entity*)getObjectFromHandle(entityHandle);
    if (entity != nullptr)
    {
        // +0x10: flags1 (ushort) - active flag (bit 15)
        // +0x12: flags2 (ushort) - disabled flag (bit 15)
        if ((*(ushort*)((int)entity + 0x10) & 0x8000) != 0 &&
            (*(ushort*)((int)entity + 0x12) & 0x8000) == 0)
        {
            return true;
        }
    }
    return false;
}