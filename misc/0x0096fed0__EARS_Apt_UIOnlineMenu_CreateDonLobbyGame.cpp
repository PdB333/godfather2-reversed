// Xbox PDB: EARS_Apt_UIOnlineMenu_CreateDonLobbyGame
// FUNC_NAME: MultiplayerLobbyManager::setupLobby

#include <cmath>

// Global data references (guessed)
extern int gLobbyType;                // DAT_00d5ddec
extern float gCurrentTime;            // DAT_01129908 + 0x14 (time in seconds)
extern bool gIsOnlineEnabled;         // DAT_01223484
extern int gMaxPlayers;               // DAT_0113082c
extern int gMaxTeams;                 // DAT_01130808

// Forward declarations for called functions
void* allocateMemory(size_t size);                  // FUN_009c8e50
void* createNetSession(int flags);                  // FUN_00982280
void setGameMode(int a, int b);                     // FUN_00981f10
void showLoadingText(const char* text);             // FUN_00981eb0
void setReady(int ready);                           // FUN_00982400
void startSession();                                // FUN_00982e10
int  getLocalPlayerId(int);                         // FUN_0095cad0
void addPlayerToSession(void* session, int playerId, int something); // FUN_008a42b0
void changeMenuState(const char* state, int a, int b); // FUN_00983120

class MultiplayerLobbyManager {
public:
    // Virtual function table at offset 0
    // vtable[3] (offset 0x0C) is called at the end, maybe 'proceed' or 'enterState'

    // Offset layout (in int units):
    // +0x00: vtable
    // ...
    // +0x6A: m_pSession (?) (offset 0x1A8 bytes)
    // +0x6F: m_teamCount (offset 0x1BC bytes)
    // +0x74: m_playerLimit (offset 0x1D0 bytes)
    // +0x78: m_bReady (offset 0x1E0 bytes)
    // +0x79: m_bCreated (offset 0x1E4 bytes)
    // +0x7A: m_lastUpdatedTime (offset 0x1E8 bytes)
    // +0x7B: m_lobbyType (offset 0x1EC bytes)
    // +0x7C: m_lobbyId (offset 0x1F0 bytes)
    // +0x7D: m_bActive (byte, offset 0x1F4 bytes)
    // +0x8F: m_bExitRequested (offset 0x23C bytes)

    void setupLobby();
};

void __fastcall MultiplayerLobbyManager::setupLobby(int* thisPtr)
{
    float fCurrentTime = *(float*)((int)&gCurrentTime);  // from global
    int iLobbyType = gLobbyType;                         // DAT_00d5ddec
    int iRoundedTime = (int)std::round(fCurrentTime);    // local_8
    void* session = nullptr;
    int newSession = 0;

    // Set initial flags
    *(char*)(thisPtr + 0x7D) = 1;   // m_bActive = true
    thisPtr[0x79] = 1;              // m_bCreated = 1
    thisPtr[0x78] = 0;              // m_bReady = 0
    thisPtr[0x8F] = 0;              // m_bExitRequested = 0

    // Set lobby parameters
    thisPtr[0x7C] = iLobbyType;     // m_lobbyId = gLobbyType
    thisPtr[0x7B] = 0x42;           // m_lobbyType = 66 (fixed constant)
    thisPtr[0x7A] = iRoundedTime;   // m_lastUpdatedTime = rounded current time

    if (gIsOnlineEnabled) {
        // Set player and team limits (-1 for infinite? Or zero-based)
        thisPtr[0x74] = gMaxPlayers - 1;  // m_playerLimit
        thisPtr[0x6F] = gMaxTeams - 1;    // m_teamCount

        // Allocate session object
        session = allocateMemory(0xF0);   // 240 bytes
        if (session != nullptr) {
            newSession = (int)createNetSession(0);  // iVar4
        }

        // Configure game session
        setGameMode(2, 3);
        showLoadingText("$mp_creating_game");

        if (newSession != 0) {
            *(int*)(newSession + 0x0C) = 0xD;          // e.g., game type id
            *(int*)(newSession + 0x20) = 0xE8D242CA;   // some signature/constant
            *(void**)(newSession + 0x14) = (void*)0x0096F710; // callback function pointer (LAB)
        }
        startSession();

        // Add local player to the session
        int localPlayerId = getLocalPlayerId(0);
        addPlayerToSession((void*)(thisPtr + 0x6A), localPlayerId, 0);
    }

    // Change to online lobby state
    changeMenuState("$mp_online_enter_don_lobby", 0, 0);

    // Call virtual function at vtable[3] (offset 0x0C) - likely proceed/enter
    void (*vfunc)(void) = (void (*)())(*(int*)thisPtr + 0x0C);
    vfunc();
}