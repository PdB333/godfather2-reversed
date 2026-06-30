// FUNC_NAME: getPlayerDefinitionId
// Function at 0x004213e0: Retrieves the definition ID for the current player.
// Returns 0xFE16702F if no definition is found.
extern "C" uint32_t* __cdecl findPlayerDefinition(uint32_t playerType); // from 0x004025a0

extern "C" void __cdecl getPlayerDefinitionId(uint32_t* outDefId)
{
    uint32_t playerType;
    // Global pointer at 0x0122337c: pointer to game state instance
    uint32_t* gGameState = *(uint32_t**)0x0122337c;

    if (gGameState == nullptr) {
        playerType = 0;
    } else {
        // +0x84 offset in game state: pointer to active player object
        uint32_t* activePlayer = *(uint32_t**)(gGameState + 0x84 / 4);
        if (activePlayer != nullptr) {
            // +0x1C offset in player object: player type identifier
            playerType = *(uint32_t*)(activePlayer + 0x1C / 4);
        } else {
            playerType = 0;
        }
    }

    uint32_t* defPtr = findPlayerDefinition(playerType);
    if (defPtr != nullptr) {
        // +0x2C offset in definition structure: definition ID
        *outDefId = *(uint32_t*)(defPtr + 0x2C / 4);
        return;
    }
    *outDefId = 0xFE16702F; // sentinel for "no definition"
}