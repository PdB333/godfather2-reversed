// FUNC_NAME: Entity::Entity
undefined4 __thiscall Entity::Entity(byte initFlags)
{
    // Call base class constructor at 0x006938d0
    Entity::baseConstructor();

    // If bit 0 of initFlags is set, perform additional initialization at 0x009c8eb0
    if (initFlags & 1) {
        this->initComponent(); // FUN_009c8eb0(this)
    }

    return this;
}