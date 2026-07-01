// FUNC_NAME: EntityManager::getEntityByIndex
undefined4 __thiscall EntityManager::getEntityByIndex(int this, uint index)
{
    // +0x10c: m_entityCount (uint)
    // +0x88: m_entityArray (array of undefined4, size m_entityCount)
    if (index < *(uint *)(this + 0x10c)) {
        return *(undefined4 *)(this + 0x88 + index * 4);
    }
    return 0;
}