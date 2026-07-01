// FUNC_NAME: PlayerManager::getActivePlayer
// Function address: 0x00777310
// Returns a pointer to the currently active player (either from player list in multiplayer, or from singleplayer default function).
// Uses flags to determine whether to search through player slots or return a fallback.

int* __fastcall PlayerManager::getActivePlayer(int* this) // ECX = this
{
    int* playerList;     // derived from this+0x5c
    int* stateObject;    // derived from this+0x70, adjusted by -0x48
    int currentIndex;
    int* foundPlayer;

    playerList = *(int**)((int)this + 0x5c);
    if (*(int*)((int)this + 0x70) == 0) {
        stateObject = 0;
    } else {
        stateObject = *(int**)((int)this + 0x70) - 0x48; // subtract offset
    }

    // Check if multiplayer flag (bit 11 at stateObject+0xc88) is set
    if ((*(unsigned int*)((int)stateObject + 0xc88) >> 0xb & 1) != 0) {
        // Multiplayer: iterate over all player slots
        currentIndex = 0;
        if (*(int*)((int)playerList + 0x744) != 0) {
            do {
                // Get player pointer by index (function at 0x704110)
                foundPlayer = PlayerManager::getPlayerByIndex(currentIndex);
                // Check if player is active/connected (bit 14 at +0x1d0)
                if ((*(unsigned int*)((int)foundPlayer + 0x1d0) >> 0xe & 1) != 0) {
                    return foundPlayer;
                }
                currentIndex++;
            } while ((unsigned int)currentIndex < *(unsigned int*)((int)playerList + 0x744));
        }
        // No active player found
        return 0;
    }

    // Singleplayer: return default player from auxiliary function (0x7175b0)
    return (int*)FUN_007175b0();
}