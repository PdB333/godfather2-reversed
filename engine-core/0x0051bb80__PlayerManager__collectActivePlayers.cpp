// FUNC_NAME: PlayerManager::collectActivePlayers
// Function at 0x0051bb80 (Godfather 2, 2008)
// Collects up to 4 active player states from the global player manager (DAT_0122339c).
// +0x14: stateArray (int) - flags indicating player activity
// +0x154: numPlayers (int) - number of entries in both arrays
// +0x158: playerHandleArray (int) - player handles, -1 marks invalid slot

extern int* g_playerManager;       // DAT_0122339c
extern int* g_otherManager;        // DAT_012233a0 (condition sanity check)
extern char g_playerActiveCount;   // DAT_01162387
extern int  g_activePlayerList[4]; // DAT_01194ae0

void __cdecl PlayerManager::collectActivePlayers()
{
    char activeCount = 0;
    g_playerActiveCount = 0;

    // Early out if managers are not initialized
    if (g_playerManager == 0 || g_otherManager == 0)
        return;

    int numPlayers = *(int*)((char*)g_playerManager + 0x154);
    if (numPlayers <= 0)
        return;

    // TLS base (not used due to branch always false)
    int* fsBase = *(int**)(__readfsdword(0x2c));

    // Pointers to parallel arrays
    int* stateArray   = (int*)((char*)g_playerManager + 0x14);    // +0x14
    int* handleArray  = (int*)((char*)g_playerManager + 0x158);   // +0x158

    do
    {
        int playerState;

        // Check for zero count (dead branch - count is always >0 here)
        if (*(int*)((char*)g_playerManager + 0x154) == 0)
        {
            playerState = *(int*)(*(int*)fsBase + 0x24);
        }
        else
        {
            playerState = *stateArray;
        }

        // Collect if player is active, handle is valid, and still under limit (max 4)
        if (playerState != 0 && *handleArray != -1 && activeCount < 4)
        {
            g_activePlayerList[activeCount] = playerState;
            activeCount++;
        }

        stateArray++;
        handleArray++;
        numPlayers--;
        g_playerActiveCount = activeCount;
    } while (numPlayers != 0);
}