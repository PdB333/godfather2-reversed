// FUNC_NAME: MissionManager::handleMessage

void __thiscall MissionManager::handleMessage(int* message)
{
    // Check that the game state object pointer is valid
    // The game state is stored at this+0x10 (likely a singleton or member)
    int* gameState = *(int**)(this + 0x10);
    if (gameState == nullptr)
        return;

    // Check a specific flag at offset 0x1f58 in the game state object
    // Bit 25 (0x02000000) must be clear (e.g., not paused/disabled)
    if ((*(uint*)(gameState + 0x1f58) >> 0x19 & 1) != 0)
        return;

    // Extract message type and argument from the message structure
    int msgType = message[0];
    int msgArg  = message[1];

    if (msgType == DAT_0112dd08)  // kMsgEnterBuilding (example)
    {
        char isValid = FUN_00713200(msgArg);  // Check if the building/object is valid
        if (isValid)
        {
            FUN_00714c50(msgArg);  // Handle the building entry logic
        }
    }
    else if (msgType == DAT_0112ac90)  // kMsgStartMission (example)
    {
        if (msgArg == 0)
            return;

        char isMissionValid = FUN_007136c0(msgArg);  // Verify mission index
        if (isMissionValid)
        {
            FUN_00716880(DAT_01205228, msgArg);  // Start the mission using global manager
        }
    }
}