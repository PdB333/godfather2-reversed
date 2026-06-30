// FUNC_NAME: applyDisplayConstraintClamping

void applyDisplayConstraintClamping(void)
{
    // Copy source values to target display settings
    g_primaryWidth = g_sourceWidth;      // +0x0 (DAT_01205360 = DAT_011f38f0)
    g_primaryHeight = g_sourceHeight;    // +0x4 (DAT_01205364 = DAT_011f3910)

    // Apply high-quality or standard clamping based on a global flag
    if (g_bHighQualityFlag) {            // DAT_0110aae7 != 0
        // Enforce minimum width and maximum height at 168 (0xA8)
        if (g_adjustedWidth < 168) {
            g_adjustedWidth = 168;
        }
        if (g_adjustedHeight > 167) {
            g_adjustedHeight = 168;
        }
        g_qualityThreshold1 = 15;        // 0xF

        // Enforce minimum width and maximum height at 190 (0xBE)
        if (g_adjustedWidth < 190) {
            g_adjustedWidth = 190;
        }
        if (g_adjustedHeight > 189) {
            g_adjustedHeight = 190;
        }
        g_qualityThreshold2 = 15;        // 0xF
    } else {
        // Standard mode: same clamping but thresholds set to 0
        if (g_adjustedWidth < 168) {
            g_adjustedWidth = 168;
        }
        if (g_adjustedHeight > 167) {
            g_adjustedHeight = 168;
        }
        g_qualityThreshold1 = 0;

        if (g_adjustedWidth < 190) {
            g_adjustedWidth = 190;
        }
        if (g_adjustedHeight > 189) {
            g_adjustedHeight = 190;
        }
        g_qualityThreshold2 = 0;
    }
}