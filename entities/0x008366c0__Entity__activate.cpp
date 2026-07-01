// FUNC_NAME: Entity::activate
void __fastcall Entity::activate(Entity* this)
{
    int guid = s_globalGUID; // DAT_0112dbe0; assume a global unique identifier for the entity
    FUN_00408a00(&guid, 0); // copy the global GUID into some internal structure (could be m_id or similar)
    this->m_flags |= 0x4; // set flag bit 2 (offset 0x84), likely indicates "activated" or "ready"
}