// FUNC_NAME: Entity::Entity
undefined4 __thiscall Entity::Entity(undefined4 this, byte allocFlag) {
    // Call base class constructor (likely Object::Object at 0x004083d0)
    FUN_004083d0(this);
    // If the allocation flag has bit 0 set, perform additional initialization
    // common pattern for dynamic allocation: register with memory manager or pool
    if ((allocFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }
    return this;
}