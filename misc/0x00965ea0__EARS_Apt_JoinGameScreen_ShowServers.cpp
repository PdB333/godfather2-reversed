// Xbox PDB: EARS_Apt_JoinGameScreen_ShowServers
// FUNC_NAME: NetSession::setupClientVersionAndJoinData
void NetSession::setupClientVersionAndJoinData(void)
{
    int iVar1;
    int iVar2;

    // Send UI command to set client version (string, param0, data pointer, param1, version number)
    uiCommand("SetClientVersion", 0, &DAT_00d8cdec, 1, *(int *)(g_netSession + 0x1f5));
    iVar1 = g_netSession;
    // Clear some state at offset +0x110
    *(undefined4 *)(g_netSession + 0x110) = 0;
    // Send UI command to show join data (string, param0, data pointer, param0)
    uiCommand("ShowJoinData", 0, &DAT_00d8cdec, 0);
    // Clear byte at offset +0x220
    *(undefined1 *)(iVar1 + 0x220) = 0;
    iVar2 = g_netSession;
    // Copy data from offset +0x6f8 to +0x1b0 (likely a state or buffer copy)
    *(undefined4 *)(g_netSession + 0x1b0) = *(undefined4 *)(g_netSession + 0x6f8);
    // Set state to 6 (e.g., lobby state)
    setSessionState(6);
    // Set up a state machine callback at offset +0x10 with a label and parameter 1
    setStateMachineCallback(iVar2 + 0x10, &LAB_0096fba0, 1);
    // If the byte at offset +0x144 is zero, deactivate a UI button
    if (*(char *)(iVar1 + 0x144) == '\0') {
        uiCommand("DeactivateButton", 0, &DAT_00d8cdec, 1, &DAT_00d796d0);
    }
    return;
}