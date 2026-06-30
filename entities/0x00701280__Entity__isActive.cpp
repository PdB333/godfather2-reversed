// FUNC_NAME: Entity::isActive
// Address: 0x00701280
// Checks if the entity has an active flag at offset +0x328
bool __fastcall Entity::isActive() const
{
    return *(int*)(this + 0x328) != 0;
}