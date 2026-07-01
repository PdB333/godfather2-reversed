// FUNC_NAME: Entity::setActive
void __thiscall Entity::setActive(Entity* this, bool enable)
{
    if (enable) {
        // Set bit 5 (0x20) in flags at offset +0x128
        this->flags |= 0x20; // +0x128: e.g., m_stateFlags or m_activeMask
        onActivated(); // 0x007f63e0: global activation handler
    } else {
        this->flags &= ~0x20;
        onDeactivated(); // 0x007f6420: global deactivation handler
    }
}