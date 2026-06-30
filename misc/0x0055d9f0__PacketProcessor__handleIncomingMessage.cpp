// FUNC_NAME: PacketProcessor::handleIncomingMessage
// Address: 0x0055d9f0
// Role: Processes an incoming packet/message header by copying 12 bytes from input buffer
// and appending a 4-byte constant (likely message type/magic). Calls a logging function
// if game state matches a specific phase (0x07 = in-mission?), then passes the 16-byte
// structure to the main message handler.
// Register usage: EAX -> input buffer (12 bytes), ESI -> current manager instance (e.g., GameManager)
// The fourth word of the output structure is overridden with a global constant.

// Global constant used as fourth word, likely a message type ID or version
extern const uint32_t gMessageTypeConstant = DAT_00e2b1a4; // 0x00e2b1a4

void handleIncomingMessage(void)
{
    uint32_t stackBuffer[4]; // 16-byte structure

    // Read first three words from input buffer (pointed by EAX)
    stackBuffer[0] = *in_EAX;
    stackBuffer[1] = in_EAX[1];
    stackBuffer[2] = in_EAX[2];

    // Override fourth word with global constant
    stackBuffer[3] = gMessageTypeConstant;

    // Check game state: manager at ESI +0x18 points to a state structure,
    // byte at +0xD8 compared to 0x07 (e.g. "in mission" or "active")
    if (*(char*)(*(uint32_t*)(unaff_ESI + 0x18) + 0xD8) == 0x07) {
        // Log debug info (1,1,0) – likely log parameters
        FUN_009f4240(1, 1, 0);
    }

    // Process the 16-byte packet structure
    FUN_009f4c40(&stackBuffer);
}