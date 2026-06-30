// FUNC_NAME: UnknownClass::getTimeDeltaAndExpiredWithFallback
// Function address: 0x0054f220
// Likely part of a timing system using a cached timestamp at offset +0x94 (m_lastTimestamp)
// Global DAT_01205224 is the current game time (presumably in some tick unit)
// Returns a packed uint: high 24 bits = (delta >> 8), low 8 bits = (timeLimit <= delta)

uint __thiscall UnknownClass::getTimeDeltaAndExpiredWithFallback(uint fallbackTime, uint timeLimit)
{
    uint result = fallbackTime & 0xFFFFFF00;  // Mask out low byte from fallback

    // +0x94 is the cached timestamp (e.g., last update time)
    if (m_lastTimestamp != 0)
    {
        uint delta = g_currentTime - m_lastTimestamp;  // DAT_01205224
        bool expired = (timeLimit <= delta);
        // Pack: high 24 bits = delta / 256, low byte = expired flag
        result = (delta >> 8) | (expired ? 1 : 0);
    }
    return result;
}