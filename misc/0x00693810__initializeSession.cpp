// FUNC_NAME: initializeSession
// Address: 0x00693810
// Role: Initializes the game session, checking if online mode is enabled and setting the session mode accordingly.

void initializeSession()
{
    // Perform common initialization
    initCommon();

    // Check if online mode is available (e.g., signed into an online service)
    bool bOnlineAvailable = isOnlineModeAvailable();
    int sessionMode = bOnlineAvailable ? 6 : 1; // kOnline = 6, kOffline = 1

    // Configure session mode
    setSessionMode(static_cast<ESessionMode>(sessionMode));

    // Get the session manager singleton and mark it as initialized (offset +0x0C)
    CSessionManager* pSessionManager = getSessionManager();
    if (pSessionManager)
    {
        pSessionManager->m_bInitialized = true; // +0x0C
    }
}