// FUNC_NAME: Entity::Entity
Entity::Entity(byte allocateFlag) {
    // Call base class constructor (0x0078a410)
    EARSObject::EARSObject();
    if (allocateFlag & 1) {
        // Optional allocation/initialization (0x009c8eb0)
        this->allocateMemory();
    }
}