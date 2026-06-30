// FUNC_NAME: Entity::forwardToComponent
// Function at 0x006b3c60: delegates call to embedded component at offset 0x9c
void Entity::forwardToComponent(uint param2) {
    this->m_component.process(param2);
}