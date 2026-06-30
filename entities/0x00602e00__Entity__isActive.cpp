// FUNC_NAME: Entity::isActive
bool __thiscall Entity::isActive() {
    // +0x34: m_activeFlag (non-zero means active)
    return *(int*)((char*)this + 0x34) != 0;
}