// FUNC_NAME: NetSession::clearHostList
void NetSession::clearHostList(void)
{
    // Log the clearing operations
    debugPrint("ClearHostsList", 0, &g_hostListData, 0);
    debugPrint("ClearHostInfo", 0, &g_hostListData, 0);

    // Reset the refreshing flag
    this->m_bRefreshing = false; // +0x220

    // Restore the original host count to current
    this->m_currentHostCount = this->m_originalHostCount; // +0x1b0 = +0x6f8

    // Set state to 6 (e.g., kStateIdle or kStateCleared)
    setState(6);

    // Schedule a callback after 1 unit (likely 1 second) to refresh the list
    setTimer(this + 0x10, &NetSession::onHostListCleared, 1);
}