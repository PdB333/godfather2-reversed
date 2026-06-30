// FUNC_NAME: Entity::getType
uint32_t __thiscall Entity::getType(Entity* this) {
    // Returns the object type identifier stored at offset +0x40
    return *(uint32_t*)((uint8_t*)this + 0x40);
}