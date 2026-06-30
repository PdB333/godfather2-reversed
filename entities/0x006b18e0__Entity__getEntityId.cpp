// FUNC_NAME: Entity::getEntityId
// Function address: 0x006b18e0
// Role: Returns the entity ID stored as the first field (offset +0x0) of the Entity object.
// This is a simple accessor used to retrieve the 32-bit identifier.

uint32_t Entity::getEntityId() const {
    return *reinterpret_cast<const uint32_t*>(this);
}