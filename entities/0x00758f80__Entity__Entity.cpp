// FUNC_NAME: Entity::Entity

Entity* __thiscall Entity::Entity(byte flags) {
    this->initializeBase(); // FUN_00757b30 – base class constructor
    if ((flags & 1) != 0) {
        this->registerWithManager(); // FUN_00624da0 – post‑construction registration
    }
    return this;
}