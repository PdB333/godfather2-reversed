// FUNC_NAME: checkAndUpdatePlayerController
// Address: 0x0053de70
// Role: Checks whether the player's controller is active and triggers an update if so.

// External globals (addresses based on Ghidra data)
extern unsigned char g_playerControllerArray; // Base at 0x01198ec4, array of 0x1b-byte structures
extern int g_playerIndex;                     // At 0x0121bf30, current player index (0-based)

// Forward declaration of the update function (called when controller is active)
extern void updatePlayerController(void);     // At 0x006063b0

void checkAndUpdatePlayerController(void)
{
    // Interpret the byte at offset (g_playerIndex * 0x1b) in the controller array.
    // This byte is the "isConnected" flag of the current player's controller structure.
    unsigned char* controllerIsActive = (unsigned char*)&g_playerControllerArray + g_playerIndex * 0x1b;

    if (*controllerIsActive != 0)
    {
        updatePlayerController();
    }
}