// FUNC_NAME: Entity::getOwnerEntity
int Entity::getOwnerEntity() const {
    // +0xff0: pointer to an embedded sub-object (component) that is located at offset 0x48 in the owner
    if (this->m_pComponent != 0) {
        // Subtract the known offset to retrieve the base of the owning entity
        return (int)((char*)this->m_pComponent - 0x48);
    }
    return 0;
}