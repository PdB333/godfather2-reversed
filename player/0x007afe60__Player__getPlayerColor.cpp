// FUNC_NAME: Player::getPlayerColor
uint32_t Player::getPlayerColor() {
    uint32_t color = 0; // default (in_EAX & 0xffffff00 from decompiled code, likely a cached value)

    // Check flag at offset +0x8E6 (bit 0) – possibly "use default color" flag
    if ((m_flags & 1) == 0) {
        // Flag is clear: determine color based on don control state
        if (isDonControlActive()) {
            // Don control active – use special color index 0x24
            color = getColorFromTable(getColorTableEntry(0x24));
        } else {
            // Normal state – use standard color index 0x23
            color = getColorFromTable(getColorTableEntry(0x23));
        }
    }
    // If flag is set, return the default color (from EAX, likely a previous result)
    return color;
}