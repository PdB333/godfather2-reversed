// FUNC_NAME: Entity::getID
// Address: 0x0061ee00
// Role: Returns the entity's unique identifier, initializing it if necessary.
// Offsets: this+0x04 = m_entityID (uint32), this+0x8c = m_bIDValid (bool)

uint32_t Entity::getID() {
    if (!m_bIDValid) {
        generateID();
    }
    return m_entityID;
}