// Xbox PDB: EARS_Apt_GamecardPopupScreen_ShowScreen
// FUNC_NAME: GamertagPopup::showGamertagPopup
// Reconstructed C++ for gamertag popup display (address 0x00967c80)
// This function clears, populates, and shows a gamertag popup based on the given type.
// Types: 5 = all players, 7 = spectators.

class GamertagPopup {
public:
    // +0x00: m_popupType – the type of popup to show
    int m_popupType;

    // Shows the gamertag popup with the specified type.
    void showGamertagPopup(int popupType);
};

// Global game manager pointer (presumably a singleton)
// +0xDC: m_popupCommand (set to 12 to indicate show)
// +0x2BC: m_popupSomething (cleared to 0)
// +0x338: m_playerList (array of player info pointers)
// +0x33C: m_playerCount
// +0x3C4: m_spectatorList (array of spectator info pointers)
// +0x3C8: m_spectatorCount
extern int* gGameManager;

// UI messaging function: sends a command to the UI system.
// Signature: void sendUIMessage(const char* command, int param, void* data, int flag, ...)
void __thiscall sendUIMessage(const char* command, int param, void* data, int flag, ...);

void __thiscall GamertagPopup::showGamertagPopup(int popupType)
{
    int* gameManager = gGameManager;
    this->m_popupType = popupType;            // store the popup type

    // Set UI state for the popup
    *(int*)(gameManager + 0xDC)  = 12;        // +0xDC: command = 12 (show)
    *(int*)(gameManager + 0x2BC) = 0;         // +0x2BC: clear something

    // Clear existing gamertag entries
    sendUIMessage("ClearGamertagPopup", 0, &DAT_00d8cdec, 0);

    if (this->m_popupType == 5)               // All players
    {
        uint playerCount = *(uint*)(gameManager + 0x33C);
        if (playerCount != 0)
        {
            int** playerArray = *(int***)(gameManager + 0x338);
            for (uint i = 0; i < playerCount; i++)
            {
                // Each player info structure has the gamertag string at offset +0x20
                char* gamertag = (char*)(playerArray[i] + 0x20);
                sendUIMessage("AddGamertag", 0, &DAT_00d8cdec, 1, gamertag);
            }
        }
    }
    else if (this->m_popupType == 7)          // Spectators
    {
        uint spectatorCount = *(uint*)(gameManager + 0x3C8);
        if (spectatorCount != 0)
        {
            int** spectatorArray = *(int***)(gameManager + 0x3C4);
            for (uint i = 0; i < spectatorCount; i++)
            {
                char* gamertag = (char*)(spectatorArray[i] + 0x20);
                sendUIMessage("AddGamertag", 0, &DAT_00d8cdec, 1, gamertag);
            }
        }
    }

    // Display the popup with all added gamertags
    sendUIMessage("ShowGamertagPopup", 0, &DAT_00d8cdec, 0);
}