// Xbox PDB: EARS_Apt_UIHud_ShowVenueAttack
// FUNC_NAME: Player::showVenueAttack

// Reconstructed C++ for function at 0x0093c970
// Likely Player::showVenueAttack (initiates venue attack UI sequence)
// Offsets: +0x5c flags, +0x50 message buffer, +0x10 state machine,
//          +0x13c venueId, +0x140 progress, +0x16c skip flag, +0x170 attackData

void __thiscall Player::showVenueAttack(int this, int venueId)
{
    // Bit 12 at +0x5c indicates venue attack UI already active
    if (((*(unsigned int *)(this + 0x5c) >> 0xc) & 1) == 0) {
        // Mark as active
        *(unsigned int *)(this + 0x5c) |= 0x1000;

        // Store venue ID and clear progress counter
        *(int *)(this + 0x13c) = venueId;
        *(char *)(this + 0x140) = 0;

        // Format a string (likely the venue ID) into a 16-byte buffer
        char formatBuffer[16];
        sprintf(formatBuffer, "%d", venueId);  // Assume DAT_00e3266c is "%d"

        // Broadcast UI event "ShowVenueAttack" with the formatted string
        broadcastUIEvent("ShowVenueAttack", 0, &DAT_00d8a64c, 1, formatBuffer);

        // Start a timer/callback with global data (DAT_01130238)
        // local struct mimics a timer structure
        int timerData[3] = { DAT_01130238, 0, 0 };
        startDelayedCallback(timerData, 0);

        // Send messages to two global targets (if non-zero)
        if (DAT_0112a5a4 != 0) {
            sendMessage(this + 0x50, &DAT_0112a5a4, 0x8000);
        }
        if (DAT_01130248 != 0) {
            sendMessage(this + 0x50, &DAT_01130248, 0x8000);
        }

        // Set attack data pointer (global + offset) and clear skip flag
        *(int *)(this + 0x170) = DAT_01205224 + 0x9c4;
        *(char *)(this + 0x16c) = 0;

        // Transition state machine at +0x10 to a new state (LAB_0093bd50)
        setState(this + 0x10, &LAB_0093bd50, 1);
    }
    return;
}