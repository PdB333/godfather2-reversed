// FUNC_NAME: PlayerManager::setPlayerControlEnabled
// Function at 0x00566ab0: Sets a control-enabled flag on the player object (at +8) and updates a bitmask at +0x2c.
// The flag at player+0x33d is written directly, and bit 1 (0x2) of m_flags reflects the same state.

void __thiscall PlayerManager::setPlayerControlEnabled(char enabled)
{
    // Player object pointer stored at offset +0x08 in this manager
    Player* player = *(Player**)(this + 8);
    if (player != 0) {
        // Write enabled flag at player offset 0x33d (likely a boolean control state)
        *(char*)(player + 0x33d) = enabled;
    }

    // Update the local bitmask at +0x2c: bit 1 = control enabled
    if (enabled != 0) {
        *(uint32_t*)(this + 0x2c) |= 2;      // set bit 1
    } else {
        *(uint32_t*)(this + 0x2c) &= ~2;     // clear bit 1
    }
}