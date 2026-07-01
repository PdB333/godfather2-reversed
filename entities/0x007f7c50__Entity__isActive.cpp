// FUNC_NAME: Entity::isActive
bool Entity::isActive() const
{
    // offset +0xff8: m_active (char flag)
    return *(char*)((uintptr_t)this + 0xff8) > 0;
}