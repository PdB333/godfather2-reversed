// FUNC_NAME: Entity::initializeSubComponents
void __thiscall Entity::initializeSubComponents(Entity *this, int contextParam) {
    // +0x90: flag indicating if first subsystem is initialized
    if (*(char *)((uintptr_t)this + 0x90) == '\0') {
        Entity::initFirstSubsystem(contextParam);
    }
    // +0x80: flag indicating if second subsystem is initialized
    if (*(char *)((uintptr_t)this + 0x80) == '\0') {
        Entity::initSecondSubsystem(contextParam);
    }
}