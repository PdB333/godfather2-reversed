// FUNC_NAME: Entity::deactivateChildIfFlagSet
// Address: 0x008bf860
// Role: Checks bit 5 of flags at +0x84; if set, clears it and deactivates the child object at +0x54.
// Called from Entity::update (0x008bc5f0) during each update loop to process pending deactivation.

void __fastcall Entity::deactivateChildIfFlagSet(Entity* this) {
    // +0x84: m_flags (bitmask)
    if ((this->m_flags & 0x20) != 0) {
        // Clear bit 5 (0x20) – pending deactivation
        this->m_flags &= ~0x20;
        // +0x54: m_child (pointer to another entity)
        // Call child deactivation (second param = 1 means disable)
        FUN_006b08c0(this->m_child, 1); // likely setActive(child, false)
    }
}