// FUN_0041e4d0: QualityManager::applyQualitySettings
// Applies three quality settings with per-category min/max caps (0x37=55, 0x35=53, 0x36=54).
// Each setting is clamped to a valid range by adjusting global cap variables.

// Global cap variables
static int g_minQualityCap;   // DAT_012058d0 - minimum quality cap (e.g., for texture quality)
static int g_maxQualityCap;   // DAT_00f15988 - maximum quality cap
static int g_qualitySetting0; // _DAT_011f3ab4 - quality setting 0
static int g_qualitySetting1; // _DAT_011f3aac - quality setting 1
static int g_qualitySetting2; // _DAT_011f3ab0 - quality setting 2

void applyQualitySettings(int setting0, int setting1, int setting2)
{
    // Apply first setting (likely texture quality, cap = 0x37)
    if (g_minQualityCap < 0x37) {
        g_minQualityCap = 0x37;
    }
    if (0x37 < g_maxQualityCap) {
        g_maxQualityCap = 0x37;
    }
    g_qualitySetting0 = setting0;

    // Apply second setting (likely shadow quality, cap = 0x35)
    if (g_minQualityCap < 0x35) {
        g_minQualityCap = 0x35;
    }
    if (0x35 < g_maxQualityCap) {
        g_maxQualityCap = 0x35;
    }
    g_qualitySetting1 = setting1;

    // Apply third setting (likely lighting quality, cap = 0x36)
    if (g_minQualityCap < 0x36) {
        g_minQualityCap = 0x36;
    }
    if (0x36 < g_maxQualityCap) {
        g_maxQualityCap = 0x36;
        g_qualitySetting2 = setting2;
        return;
    }
    g_qualitySetting2 = setting2;
}