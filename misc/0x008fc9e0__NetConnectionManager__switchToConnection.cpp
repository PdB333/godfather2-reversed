// FUNC_NAME: NetConnectionManager::switchToConnection
// Function at 0x008fc9e0: Replace the active network connection with a new one.
void __thiscall NetConnectionManager::switchToConnection(void* this, void* newConnection)
{
    // +0x1c: pointer to current connection object
    void* oldConnection = *(void**)((int)this + 0x1c);

    if (oldConnection != 0) {
        // Format connection identifier from old connection: e.g., session/player IDs at +0x70, +0x74
        char oldBuffer[128]; // Assume sufficient size
        snprintf(oldBuffer, sizeof(oldBuffer), "%04X.%04X", *(unsigned short*)((int)oldConnection + 0x70), *(unsigned short*)((int)oldConnection + 0x74));
        const char* oldStr = oldBuffer[0] ? oldBuffer : "<null>";
        // Log: tag SPGP (0x53504750) and sub-tag CHKC (0x43484b43)
        debugPrint(0x53504750, 0x43484b43, oldStr);
        debugFlush(0x53504750);
        // Free the old buffer (if dynamically allocated)
        // (destructor call omitted for clarity)
    }

    // Clear bit 0 of status flags at +0x14 (e.g., "connected" flag)
    *(unsigned int*)((int)this + 0x14) &= ~0x1;

    // Disconnect any existing connection cleanup
    if (*(int*)((int)this + 0x1c) != 0) {
        disconnectCleanup(); // FUN_008fbcf0
    }

    // Assign the new connection
    *(void**)((int)this + 0x1c) = newConnection;

    // Validate new connection's extended data (+0xdc)
    int validationResult = checkConnectionExtendedData((int)newConnection + 0xdc); // FUN_008fc140
    if (validationResult != 0) {
        setSomeFlag(0); // FUN_007dd020(0)
    }

    // Send state update after switching
    sendStateUpdate(); // FUN_008fbfe0

    // Log new connection info
    char newBuffer[128];
    snprintf(newBuffer, sizeof(newBuffer), "%04X.%04X", *(unsigned short*)((int)newConnection + 0x70), *(unsigned short*)((int)newConnection + 0x74));
    const char* newStr = newBuffer[0] ? newBuffer : "<null>";
    // Log: tag SPGP, sub-tag CHKS (0x43484b53)
    debugPrint(0x53504750, 0x43484b53, newStr);
    // Free new buffer if dynamically allocated
    // (destructor call omitted)
}