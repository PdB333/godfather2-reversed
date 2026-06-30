// FUNC_NAME: Entity::getComponent
bool __thiscall Entity::getComponent(Entity *this, uint32_t *outComponent) {
    // +0x38: pointer to a component (e.g., state machine, manager)
    if (outComponent != nullptr) {
        *outComponent = *(uint32_t *)((uint8_t *)this + 0x38);
    }
    return *(uint32_t *)((uint8_t *)this + 0x38) != 0;
}