// FUNC_NAME: setGlobalValue
// Address: 0x004e0660
// Simple setter: stores a 32-bit value into a global variable at 0x0116407c.
// This global is likely a singleton pointer or a game state flag.
// Called from various initialization / configuration points (e.g., 0x00681840).
void setGlobalValue(uint32_t value)
{
    // Global storage at 0x0116407c (type: uint32_t)
    g_globalValue = value;
}