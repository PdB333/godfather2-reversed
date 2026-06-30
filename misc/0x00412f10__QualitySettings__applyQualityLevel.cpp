// FUNC_NAME: QualitySettings::applyQualityLevel
// Function at 0x00412f10: Applies a quality level setting, clamping min/max bounds.
// Reads/writes globals: g_gameQuality (DAT_012058d0), g_renderQualityMax (DAT_00f15988), g_currentQualitySetting (_DAT_011f3a10)
// Typically called when changing graphics options.

void QualitySettings::applyQualityLevel(byte qualityLevel)
{
    // Enforce minimum quality level (offset +0x0? g_gameQuality)
    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe; // +0x0? minimum quality index (14)
    }
    // Enforce maximum quality level if exceeded
    if (0xe < DAT_00f15988) {                   // +0x4? g_renderQualityMax
        DAT_00f15988 = 0xe;                     // clamp max to 14
        _DAT_011f3a10 = (uint)qualityLevel;     // +0x8? store applied quality
        return;
    }
    // Otherwise just store the quality level
    _DAT_011f3a10 = (uint)qualityLevel;
}