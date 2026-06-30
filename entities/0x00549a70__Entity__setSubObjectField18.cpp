// FUNC_NAME: Entity::setSubObjectField18
void Entity::setSubObjectField18(uint32_t value) {
    // +0x18: pointer to sub-object (e.g., RenderData, StateData)
    // Sub-object +0x18: 32-bit field to set (e.g., color, flag)
    *(uint32_t*)(*(uint32_t*)(this + 0x18) + 0x18) = value;
}