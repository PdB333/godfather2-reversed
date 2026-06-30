// FUNC_NAME: GameObjectManager::resolveHandle(GameHandle* handle)
int GameObjectManager::resolveHandle(GameHandle* handle) {
    // handle->slotIndex at param_2+0x04
    // m_objectArray at this+0x1c (pointer to array of 0x10-byte entries)
    return m_objectArray + (handle->slotIndex * 0x10);
}