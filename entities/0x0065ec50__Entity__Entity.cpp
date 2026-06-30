// FUNC_NAME: Entity::Entity
void* __thiscall Entity::Entity(byte constructFlags) {
    this->commonInit(); // FUN_0065ec70 - initialize common members (vtable, etc.)
    if ((constructFlags & 1) != 0) {
        this->callBaseConstructor(); // FUN_009c8eb0 - call base class constructor
    }
    return this;
}