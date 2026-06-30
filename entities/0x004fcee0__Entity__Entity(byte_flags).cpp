// FUNC_NAME: Entity::Entity(byte flags)
Entity* Entity::Entity(byte flags) {
    // Call base class default constructor (FUN_004fc9f0)
    SimObject::SimObject();

    // If the allocation flag (bit 0) is set, perform additional initialization (FUN_009c8eb0)
    if (flags & 1) {
        this->initializeAllocation();
    }

    // Return the constructed object pointer
    return this;
}