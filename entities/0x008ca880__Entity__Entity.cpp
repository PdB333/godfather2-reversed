// FUNC_NAME: Entity::Entity
// Function address: 0x008ca880
// Role: Constructor for the Entity class (base game object). Initializes vtable and performs common initialization; if param_2 & 1 is set, runs additional setup (likely for heap-allocated objects).

undefined4 * __thiscall Entity::Entity(undefined4 *this, byte initFlag) {
    // Set vtable pointer to class-specific table (offset +0x00)
    *this = &Entity_vtable; // vtable at 0x00d7bfd8

    // Call base class or common initialization routine
    Entity::initCommon(); // FUN_008cc780

    // If initFlag flag bit 0 is set, perform deferred initialization
    if ((initFlag & 1) != 0) {
        Entity::initDeferred(this); // FUN_009c8eb0(this)
    }

    return this;
}