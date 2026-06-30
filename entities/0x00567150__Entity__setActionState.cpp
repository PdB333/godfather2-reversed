// FUNC_NAME: Entity::setActionState
void __thiscall Entity::setActionState(Entity* this, int targetId)
{
    // +0x10: actionType (set to 9, likely an enum value for a specific action)
    this->field_0x10 = 9;
    // +0x14: actionSubType (set to 2, possibly a sub-state or variant)
    this->field_0x14 = 2;
    // +0x18: targetId (parameter, e.g., entity ID or target reference)
    this->field_0x18 = targetId;
}