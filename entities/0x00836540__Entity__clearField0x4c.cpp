// FUNC_NAME: Entity::clearField0x4c
void __thiscall Entity::clearField0x4c(Entity* this) {
    // +0x4c: often used as a flag or state (e.g., bIsActive, m_nFlags, etc.)
    *(int32_t*)((uint8_t*)this + 0x4c) = 0;
}