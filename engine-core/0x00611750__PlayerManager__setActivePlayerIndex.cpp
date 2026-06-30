// FUNC_NAME: PlayerManager::setActivePlayerIndex
void __thiscall PlayerManager::setActivePlayerIndex(int thisPtr, int playerIndex)
{
    // +0x100: m_ActivePlayerIndex - the currently selected player slot
    *(int *)(thisPtr + 0x100) = playerIndex;
    
    // +0xfc: m_bInitialized - whether the manager has been fully set up
    // Check if this is the global singleton PlayerManager instance (DAT_012058e8)
    // and if the manager is initialized, then fire an update callback.
    if (g_PlayerManager == thisPtr && *(int *)(thisPtr + 0xfc) != 0) {
        // FUN_006063b0 - handles re-initialization or state refresh when active player changes
        PlayerManager::onActivePlayerChanged();
    }
    return;
}