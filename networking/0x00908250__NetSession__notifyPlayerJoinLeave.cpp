// FUNC_NAME: NetSession::notifyPlayerJoinLeave
// Address: 0x00908250
// Called when a player joins (action=0) or leaves (action=1) the game session.
// Uses global session singleton (DAT_01223484) and a function table (DAT_012234E0) for sending network messages.

#include <cstring>

// Forward declarations of global variables (actual addresses defined elsewhere)
extern uint8_t* DAT_01223484; // Pointer to the game session singleton (e.g., NetSession)
extern uint8_t* DAT_012234E0; // Pointer to a function table for network messaging
extern const char DAT_0120546e[]; // Default player name (likely empty string)

void NetSession::notifyPlayerJoinLeave(int action) {
    // Offset +0x350 in the session singleton: pointer to the player's name string (char*)
    char* playerName = *(char**)(DAT_01223484 + 0x350);
    if (playerName == nullptr) {
        playerName = (char*)DAT_0120546e; // Use default name if none set
    }

    // Copy at most 15 characters + null terminator into a local buffer
    char nameBuffer[16];
    strncpy(nameBuffer, playerName, 16);
    nameBuffer[15] = '\0'; // Ensure null termination

    // Resolve the messaging function from the table at DAT_012234E0
    // The table is likely a vtable-like structure; offset +0x14 points to a function
    // Signature: void (__cdecl*)(uint32_t messageType, uint32_t command, const char* playerName)
    auto sendMessage = (void(__cdecl*)(uint32_t, uint32_t, const char*))(*DAT_012234E0 + 0x14);

    // Standard message type identifier (possibly "MPGP" = MultiPlayer Game Protocol)
    const uint32_t kMessageType = 0x4D504750;

    if (action == 0) {
        // Player joining: construct the JOIN command with optional active flag
        int activeFlag = *(int*)(DAT_01223484 + 8); // +0x8: non-zero if player is active
        // Conditionally add 0xFE000A06 to the base JOIN command (0x4A4F494E) when active flag is set
        uint32_t command = 0x4A4F494E; // "JOIN"
        if (activeFlag != 0) {
            command += 0xFE000A06; // Combined with active flag modifier
        }
        sendMessage(kMessageType, command, nameBuffer);
    } else if (action == 1) {
        // Player leaving: send LEAVE command (0x4C454156 = "LEAV")
        sendMessage(kMessageType, 0x4C454156, nameBuffer);
    }
}