// FUNC_NAME: Entity::isScriptObjectAlive
bool __fastcall Entity::isScriptObjectAlive() const
{
    // +0x34: m_flags (bit0 = kFlagDestroyed)
    if (m_flags & 1)
        return false;

    // +0x40: m_scriptObjectHandle (handle or pointer to script object)
    if (m_scriptObjectHandle == nullptr)
        return false;

    // Resolve the script object via engine function (returns pointer to script object)
    void* scriptObj = Engine::getScriptObject(m_scriptObjectHandle);
    if (scriptObj == nullptr)
        return false;

    // +0x84: script object flags, bit5 = kScriptFlagDead
    if (*(uint32_t*)((uint8_t*)scriptObj + 0x84) & 0x20)
        return false;

    return true;
}