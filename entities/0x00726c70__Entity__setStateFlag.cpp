// FUNC_NAME: Entity::setStateFlag
// Address: 0x00726c70
// Role: Sets a state flag and triggers callback if a second flag is already set

void __thiscall Entity::setStateFlag(Entity* this)
{
    // +0x114: byte flags for state management
    this->stateFlags |= 0x01;  // set pending/request flag

    if (this->stateFlags & 0x02) {  // if another flag is active
        this->stateFlags &= ~0x02;  // clear that flag
        Entity::onStateChange(this); // FUN_00727f30
    }
}