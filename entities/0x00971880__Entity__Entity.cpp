// FUNC_NAME: Entity::Entity

Entity* __thiscall Entity::Entity(byte flags) {
    // Call base class constructor via ECX (implicit this)
    baseConstructor();
    // If bit 0 is set, perform additional initialization
    if (flags & 1) {
        initialize();
    }
    return this;
}