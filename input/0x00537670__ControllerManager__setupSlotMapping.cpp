// FUNC_NAME: ControllerManager::setupSlotMapping
void __fastcall ControllerManager::setupSlotMapping(int playerIndex, int controllerIndex)
{
    // Set current mapping globals
    g_currentPlayerController = g_playerControllerMap[playerIndex];   // +0x0121b640[playerIndex]
    g_currentControllerPlayer = g_controllerPlayerMap[controllerIndex]; // +0x0121b6b8[controllerIndex]

    // For controller indices beyond the standard 16 (0-15), set additional data pointers
    if (controllerIndex > 15) {
        g_pCurrentControllerLargeData = &g_controllerLargeData[controllerIndex];   // +0x01219e64 + controllerIndex*0x5c
        g_pCurrentControllerMediumData = &g_controllerMediumData[controllerIndex]; // +0x0121a8a4 + controllerIndex*0x14
    }

    // Always set controller data pointer (size 0x2c)
    g_pCurrentControllerData = &g_controllerData[controllerIndex]; // +0x0121ab24 + controllerIndex*0x2c

    // Set player data pointer (size 0x2c)
    g_pCurrentPlayerData = &g_playerData[playerIndex]; // +0x0121b0b0 + playerIndex*0x2c

    // Mark slot as initialized
    g_slotInitialized = 0;
}