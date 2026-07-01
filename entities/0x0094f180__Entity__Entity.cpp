// FUNC_NAME: Entity::Entity
// Address: 0x0094f180
// Role: Constructor for Entity class with optional dynamic memory initialization

void __thiscall Entity::Entity(uint8 flags) {
    // Call base class constructor (likely EntityBase or SimObject)
    // FUN_0094f030 - assumed to be base constructor
    this->baseConstructor();

    // If the lowest bit of flags is set, perform additional dynamic allocation/init
    // FUN_009c8eb0 - assumed to be dynamic memory setup
    if (flags & 1) {
        this->initDynamicMemory();
    }
    // Return 'this' is implicit due to __thiscall ABI
}