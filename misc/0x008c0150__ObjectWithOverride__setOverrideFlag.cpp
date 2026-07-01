// FUNC_NAME: ObjectWithOverride::setOverrideFlag
// Function address: 0x008c0150
// Sets or clears bit 0x200 (bit 9) in m_flags at +0x84.
// If enabling and bit was previously 0, iterates m_trackCount times calling updateStreamingState(),
// and if global audio streaming flag at DAT_0112a590+4 is set, sends audio command (2) with m_audioId.

void __thiscall ObjectWithOverride::setOverrideFlag(bool enable)
{
    uint oldFlags = m_flags;  // +0x84

    if (enable) {
        m_flags |= 0x200;
        // If the bit was not already set
        if ((oldFlags >> 9 & 1) == 0) {
            // Process each track/child
            if (m_trackCount != 0) {  // +0x1a8
                uint i = 0;
                do {
                    updateStreamingState();  // FUN_008c8cb0
                    ++i;
                } while (i < m_trackCount);
            }
            // If global audio streaming enabled
            if (*(char *)(DAT_0112a590 + 4) != '\0') {
                audioControl(2, m_audioId, 0);  // FUN_0093f6c0
            }
        }
    } else {
        m_flags &= ~0x200;
    }
}