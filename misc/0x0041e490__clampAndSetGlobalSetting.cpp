// FUNC_NAME: clampAndSetGlobalSetting
// Function at 0x0041e490: Clamps two global bounds to 0x34 (52) and stores a parameter.
// Globals: g_minValue (at 0x012058d0), g_maxValue (at 0x00f15988), g_storedParam (at 0x011f3aa8).
void __cdecl clampAndSetGlobalSetting(unsigned char param1)
{
    // Ensure g_minValue is at least 52
    if (g_minValue < 0x34) {
        g_minValue = 0x34;
    }

    // Ensure g_maxValue is at most 52
    if (0x34 < g_maxValue) {
        g_maxValue = 0x34;
    }

    // Store the parameter (cast to unsigned int)
    g_storedParam = (unsigned int)param1;
}

// Global variable definitions (assumed extern elsewhere)
unsigned int g_minValue;   // +0x00 relative to global segment
unsigned int g_maxValue;   // +0x04 relative? (addresses differ but likely separate globals)
unsigned int g_storedParam; // +0x08 (address 0x011f3aa8, stored as unsigned int)