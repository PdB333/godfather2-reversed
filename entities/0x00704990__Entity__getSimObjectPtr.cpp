// FUNC_NAME: Entity::getSimObjectPtr
uint32_t __thiscall Entity::getSimObjectPtr(Entity* this) {
    // +0xC0: pointer to sim object (likely SimObject or component)
    return *(uint32_t*)((uint8_t*)this + 0xC0);
}