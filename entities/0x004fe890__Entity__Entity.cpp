// FUNC_NAME: Entity::Entity
// Function address: 0x004fe890
// This is a constructor for an entity object. It calls the base class constructor
// and optionally allocates memory if the allocFlag's lowest bit is set.
Entity * __thiscall Entity::Entity(Entity *this, byte allocFlag) {
    // Call base class constructor (likely EARSObject or another root)
    Entity::baseConstructor(this);
    // If allocFlag bit 0 is set, allocate memory for this object
    if (allocFlag & 1) {
        Entity::allocateMemory(this); // Custom allocator at 0x009c8eb0
    }
    return this;
}