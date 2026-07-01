// FUNC_NAME: Entity::setHandle
void __thiscall Entity::setHandle(void *this, uint32_t handle)
{
    // Offset 0x18: stores a handle (pointer or ID) to associated data
    *(uint32_t *)((char *)this + 0x18) = handle;
}