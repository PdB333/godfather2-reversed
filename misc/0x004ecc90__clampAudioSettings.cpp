// FUNC_NAME: clampAudioSettings
// Function address: 0x004ecc90
// Role: Clamps audio-related global settings to valid range (0xe = 14) and resets an initialization flag.

// Global audio variables (offsets relative to static data segment)
static int g_minAudioChannel; // +0x012058d0
static int g_audioInitFlag;   // +0x011f3a10
static int g_maxAudioChannel; // +0x00f15988

void clampAudioSettings()
{
    // Ensure minimum channel count is at least 14
    if (g_minAudioChannel < 14) {
        g_minAudioChannel = 14;
    }

    // Reset initialization flag (0 = not initialized)
    g_audioInitFlag = 0;

    // Ensure maximum channel count does not exceed 14
    if (14 < g_maxAudioChannel) {
        g_maxAudioChannel = 14;
    }
}