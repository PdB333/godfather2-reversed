// FUNC_NAME: Player::executeCommand
// Address: 0x0073f210
// Role: Command handler for player state queries (local player, player index)
// The function dispatches on commandId (expected range 10-14) to check the player index field at +0x50
// call to FUN_0077dd80 is getLocalPlayerIndex(), call to FUN_004ac640 is default base handler

int getLocalPlayerIndex(); // defined elsewhere, returns current local player index

class Player {
public:
    int m_playerIndex; // offset +0x50 - player slot index (0-3)

    bool executeCommand(int paramA, int paramB, int commandId, int paramC) {
        switch (commandId - 10) {
            case 0: // command 10: is this the local player?
                return m_playerIndex == getLocalPlayerIndex();
            case 1: // command 11: player index == 0?
                return m_playerIndex == 0;
            case 2: // command 12: player index == 1?
                return m_playerIndex == 1;
            case 3: // command 13: player index == 2?
                return m_playerIndex == 2;
            case 4: // command 14: player index == 3?
                return m_playerIndex == 3;
            default:
                // fallback to base/default handling (FUN_004ac640)
                return defaultCommandHandler(paramA, paramB, commandId, paramC);
        }
    }
};