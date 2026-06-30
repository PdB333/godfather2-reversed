// FUNC_NAME: EntityManager::clearTarget

bool EntityManager::clearTarget() {
    // Check if target indices are valid (not -1)
    // +0x2c0: m_entityId (int)
    // +0x2c4: m_entitySlot (int)
    if (this->m_entityId != -1 || this->m_entitySlot != -1) {
        // Call virtual method at vtable offset 0x80 on the entity object
        // (e.g., isAlive() / isActive())
        // +0x14: m_entityObject (pointer to entity)
        bool active = this->m_entityObject->isAlive();
        if (!active) {
            return false;
        }
        // Reset target indices to invalid
        this->m_entityId = -1;
        this->m_entitySlot = -1;
    }
    return true;
}