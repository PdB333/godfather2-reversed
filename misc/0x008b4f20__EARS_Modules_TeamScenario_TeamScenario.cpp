// Xbox PDB: EARS_Modules_TeamScenario_TeamScenario
// FUNC_NAME: MultiplayerRoundManager::MultiplayerRoundManager
undefined4* __thiscall MultiplayerRoundManager::MultiplayerRoundManager(undefined4* thisPtr, undefined4 someParam)
{
    undefined4 uVar1;

    // Call base class constructor (likely some network/game base)
    BaseClassConstructor(someParam);

    uVar1 = g_messageSystem;  // global message system pointer

    // Set up vtable for this class
    *thisPtr = &VTable_MultiplayerRoundManager;
    thisPtr[0xf] = &InterfaceVTable_Offset0x3C;   // offset 0x3C (0xf * 4)
    thisPtr[0x12] = &InterfaceVTable_Offset0x48;  // offset 0x48
    thisPtr[0x14] = &InterfaceVTable_Offset0x50;  // offset 0x50

    // Initialize round state
    thisPtr[0x62] = 3;   // m_roundState = STATE_ACTIVE or similar
    thisPtr[99] = 0;     // m_currentRound = 0
    thisPtr[100] = 0;    // m_roundTimer = 0
    thisPtr[0x65] = 0;   // m_winCondition = 0

    // Subscribe to event with ID 6
    RegisterEvent(6, uVar1);

    // Initialize score/tracking
    thisPtr[0x6c] = 0;   // m_teamScoreA = 0
    thisPtr[0x6d] = 0;   // m_teamScoreB = 0
    thisPtr[0x6e] = 0;   // m_bestPlayerScore = 0

    // Register message IDs for multiplayer round events
    Message::RegisterID(&g_iMsgMultiplayerRoundWin, "iMsgMultiplayerRoundWin");
    Message::RegisterID(&g_iMsgMultiplayerRoundLoss, "iMsgMultiplayerRoundLoss");
    Message::RegisterID(&g_iMsgMultiplayerFirstOnWinningTeam, "iMsgMultiplayerFirstOnWinningTeam");
    Message::RegisterID(&g_iMsgMultiplayerFirstOnLosingTeam, "iMsgMultiplayerFirstOnLosingTeam");

    return thisPtr;
}