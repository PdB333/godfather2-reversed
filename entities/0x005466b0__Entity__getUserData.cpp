// FUNC_NAME: Entity::getUserData
uint32_t __fastcall Entity::getUserData(Entity* this) {
    // Returns the 4-byte value stored at offset 0x2e8 in the Entity object.
    // This is likely a pointer to a component, a flag field, or an identifier.
    return *(uint32_t*)((uint8_t*)this + 0x2e8);
}