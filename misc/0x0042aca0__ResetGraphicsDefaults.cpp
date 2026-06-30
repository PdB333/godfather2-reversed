// FUNC_NAME: ResetGraphicsDefaults

// Global variables representing display/graphics settings
extern int g_bFullscreen;          // 0x011f41dc
extern int g_bVsync;               // 0x011f41e0
extern int g_bTripleBuffering;     // 0x011f41e4
extern int g_bGammaEnabled;        // 0x011f41f8
extern int g_bHDR;                 // 0x011f41f4
extern int g_anisotropyLevel;      // 0x011f41e8
extern int g_antialiasing;         // 0x011f41ec
extern int g_renderWidth;          // 0x011f41f0
extern int g_textureQuality;       // 0x0110b874
extern int g_shadowDetail;         // 0x012058d4
extern int g_viewDistance;         // 0x00f1598c
extern int g_soundDetail;          // 0x012058d0
extern int g_waterReflection;      // 0x00f15988
extern int g_postEffectQuality;    // 0x011f3c78
extern int g_lightingQuality;      // 0x011f3cd0
extern int g_particleQuality;      // 0x011f3a34

// Initialize graphics defaults
void ResetGraphicsDefaults()
{
    // Standard quality settings (0 = off, 1 = low, 2 = medium, etc.)
    g_bFullscreen = 1;
    g_bVsync = 1;
    g_bTripleBuffering = 1;
    g_bGammaEnabled = 1;
    g_bHDR = 1;
    g_anisotropyLevel = 7;
    g_antialiasing = 0;
    g_renderWidth = 0x20;          // 32? (unusual for resolution, possibly a bitmask or quality index)
    g_textureQuality = 8;

    // Clamp shadow detail to minimum of 0xa8 (168) and then to at least 0xbe (190)
    if (g_shadowDetail < 0xa8) {
        g_shadowDetail = 0xa8;
    }
    if (g_viewDistance > 0xa7) {
        g_viewDistance = 0xa8;
    }

    g_postEffectQuality = 0xf;     // 15 – maximum quality tier

    // Further clamp shadow detail to minimum of 0xbe and view distance to maximum of 0xbe
    if (g_shadowDetail < 0xbe) {
        g_shadowDetail = 0xbe;
    }
    if (g_viewDistance > 0xbd) {
        g_viewDistance = 0xbe;
    }

    g_lightingQuality = 0xf;       // 15

    // Clamp sound detail to minimum of 0x17 (23)
    if (g_soundDetail < 0x17) {
        g_soundDetail = 0x17;
    }

    g_particleQuality = 4;

    // Clamp water reflection to maximum of 0x17
    if (g_waterReflection > 0x17) {
        g_waterReflection = 0x17;
    }
}