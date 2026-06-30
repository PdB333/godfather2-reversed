// FUN_004ddbc0: NetObject::NetObject
void __thiscall NetObject::NetObject(int id) {
    // +0x00: m_id (int) - unique identifier for this object
    this->m_id = id;
    // +0x04: m_flags (int)
    this->m_flags = 0;
    // +0x08: m_unknownPtr (int)
    this->m_unknownPtr = 0;
    // +0x0C: m_unknownShort (short) - e.g., type or state
    this->m_unknownShort = 0;
    // +0x10: m_manager (int/pointer) - result from manager retrieval
    this->m_manager = FUN_004dd960();  // likely retrieves a singleton or allocator
}