// FUNC_NAME: Entity::forwardToSubsystem
void __thiscall Entity::forwardToSubsystem(uint32_t param)
{
    // this + 0x20: pointer to a subsystem/component object
    subsystemMethod(*(uint32_t*)((uint32_t)this + 0x20), param);
}