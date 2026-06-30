// FUNC_NAME: Entity::deactivate
void Entity::deactivate(void) {
    // Flags at +0x0C: clear bit 0 (active?) and bit 31 (0x7FFFFFFE)
    this->flags &= 0x7FFFFFFE;
    if ((this->flags & 0x20000) == 0) {  // Check bit 17 (needs cleanup?)
        this->flags |= 0x20000;          // Set bit 17
        Entity::onDeactivate();          // Call internal cleanup (0x0051b120)
    }
    // Clear bit 18 (0x40000) – possibly "in update list" flag
    this->flags &= 0xFFFBFFFF;
    // Back-reference pointer at +0x08: zero the parent's slot, then clear own pointer
    if (this->pParentBackRef != nullptr) {
        *this->pParentBackRef = 0;
        this->pParentBackRef = nullptr;
    }
}