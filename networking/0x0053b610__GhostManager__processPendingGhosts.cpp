// FUNC_NAME: GhostManager::processPendingGhosts
void GhostManager::processPendingGhosts(void)
{
    // g_pNetSession is a pointer to the current NetSession instance.
    // It is compared against an uninitialized sentinel value (address of PTR_PTR_011252d8).
    if (g_pNetSession == (NetSession **)&g_netSessionUninitializedSentinel)
    {
        // g_currentSlotIndex is the current ghost slot index.
        // g_ghostInfo1Array and g_ghostInfo2Array are arrays of GhostInfo (0x38 bytes each).
        GhostInfo *pGhost1 = (GhostInfo *)(&g_ghostInfo1Array + (int)g_currentSlotIndex * 0x38);
        GhostInfo *pGhost2 = (GhostInfo *)(&g_ghostInfo2Array + (int)g_currentSlotIndex * 0x38);

        // Process the first ghost info if valid
        if (pGhost1->m_ghostPtr != 0)
        {
            attachGhost(g_netConnection, pGhost1->m_ghostPtr); // FUN_0060b020
        }

        // Process the second ghost info if valid, same sentinel check again (redundant)
        if ( (g_pNetSession == (NetSession **)&g_netSessionUninitializedSentinel) &&
             (pGhost2->m_ghostPtr != 0) )
        {
            detachGhost(g_netConnection, pGhost2->m_ghostPtr); // FUN_0060aea0
        }
    }
}