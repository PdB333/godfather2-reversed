// FUNC_NAME: Entity::isTimeWindowActive

// Reconstructed from 0x0071be20
// Checks if the object's stored time (at offset +0x28) is in the future relative to
// the current game time, and if the elapsed time from a global base time (DAT_01205228)
// modulo a mask falls below a threshold. Used for short-lived effects or range checks.

bool __thiscall Entity::isTimeWindowActive() {
    // +0x28: m_expirationTime (float) – time when this effect/state expires
    // _DAT_00d577a0: g_currentGameTime (float) – global game clock
    // _DAT_01205228: g_baseTime (float) – a reference time, often zero or fixed start
    // _DAT_00d61dc8: g_timeThreshold (float) – threshold for wrapped difference
    // _DAT_00e44680: g_timeMask (uint) – mask for modular arithmetic (e.g., 0x7FFFFFFF)

    // Check expiration: if the stored time is not in the future, return false
    if (g_currentGameTime > m_expirationTime) {
        return false;
    }

    // Compute wrapped difference between base and stored time, masked.
    // This is essentially (base - expiration) mod (mask+1) (assuming mask is all 1s).
    uint wrappedDelta = (uint)(g_baseTime - m_expirationTime) & g_timeMask;

    // Check if the wrapped delta is below threshold; if so, the window is active.
    // This handles time wrapping for continuous cycling timers.
    return (float)wrappedDelta < g_timeThreshold;
}