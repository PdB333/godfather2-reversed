// FUNC_NAME: Entity::Entity
// Function address: 0x006beeb0 - Constructor for Entity with optional initialization flag
Entity * __thiscall Entity::Entity(byte createFlag) {
    // Call base class constructor (likely BaseEntity or SimObject)
    FUN_006bea60(); // BaseEntity::BaseEntity()

    // Conditional initialization when bit 0 is set
    if (createFlag & 1) {
        FUN_009c8eb0(this); // Entity::initializeInternal()
    }

    return this;
}