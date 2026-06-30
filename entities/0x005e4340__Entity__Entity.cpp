// FUNC_NAME: Entity::Entity
// Address: 0x005e4340
// Constructor for Entity with optional initialization flag.
undefined4 __thiscall Entity::Entity(Entity* this, byte initFlags) {
    // Call base class constructor (e.g., Framework::Object constructor)
    this->baseConstruct(); // FUN_005e4360
    // If low bit set, perform additional initialization (e.g., allocate dynamic data)
    if ((initFlags & 1) != 0) {
        additionalInit(this); // FUN_009c8eb0 (free function or static helper)
    }
    return this;
}