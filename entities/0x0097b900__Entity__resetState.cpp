// FUNC_NAME: Entity::resetState
void __fastcall Entity::resetState(Entity* this) {
    *(int*)((char*)this + 0xa4) = 0;          // +0xA4: some field (e.g., m_pTarget)
    *(unsigned short*)((char*)this + 0x102) |= 2; // +0x102: flags, set bit 1 (e.g., m_bDirty)
}