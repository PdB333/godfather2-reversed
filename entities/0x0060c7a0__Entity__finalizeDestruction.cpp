// FUNC_NAME: Entity::finalizeDestruction
// Address: 0x0060c7a0
// This function finalizes the destruction of a game Entity.
// If the object is marked for destruction (m_bMarkedForDestruction at +0x28),
// it calls a cleanup helper and then the virtual destructor (vtable+0x30).
// Otherwise, it clears the destroyed flag (m_bDestroyed at +0x29).

void Entity::finalizeDestruction() {
    if (m_bMarkedForDestruction) {
        // Cleanup helper – likely removes the entity from the world and detaches children
        cleanup();
        // Call virtual destructor (vtable slot at +0x30, corresponds to ~Entity)
        destroy();
    } else {
        m_bDestroyed = false;
    }
}