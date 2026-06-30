// FUNC_NAME: adjustGraphicsQualitySettings
// Function address: 0x005322a0
// Role: Clamps graphics quality settings and applies shader capabilities based on system config.
// Called from initialization routine at 0x00531d40.

#include <cstdint>

// Global variables (inferred from data references)
extern void* gQualityConfig;            // DAT_0121bcd8
extern void* gUnknownPtr;               // DAT_0121bc20
extern int32_t gShadowQuality;          // DAT_012058d0
extern int32_t gTextureQuality;         // DAT_00f15988
extern int32_t gFlagSomething1;         // _DAT_011f3a44
extern int32_t gFlagSomething2;         // _DAT_011f3a30
extern const uint8_t gVertexShaderCap[]; // DAT_01218d80 (static buffer)
extern const uint8_t gPixelShaderCap[];  // DAT_01218dc0 (static buffer)

// Forward declaration of external function
void applyShaderCapability(void* unknown, void* shaderCap, const uint8_t* capData); // FUN_0060b020

void adjustGraphicsQualitySettings()
{
    // Apply shader capabilities from quality config if present
    if (gQualityConfig != nullptr) {
        // Offset +0x04: Vertex shader capability
        if (*(void**)((uint8_t*)gQualityConfig + 4) != nullptr) {
            applyShaderCapability(gUnknownPtr, *(void**)((uint8_t*)gQualityConfig + 4), gVertexShaderCap);
        }
        // Offset +0x08: Pixel shader capability
        if (gQualityConfig != nullptr) {  // redundant check, but present in decompiled code
            if (*(void**)((uint8_t*)gQualityConfig + 8) != nullptr) {
                applyShaderCapability(gUnknownPtr, *(void**)((uint8_t*)gQualityConfig + 8), gPixelShaderCap);
            }
        }
    }

    // Clamp shadow quality to at least 0x1B (27)
    if (gShadowQuality < 0x1B) {
        gShadowQuality = 0x1B;
    }
    // Clamp texture quality to at most 0x1B (27)
    if (gTextureQuality > 0x1A) {
        gTextureQuality = 0x1B;
    }

    // Set flag 1
    gFlagSomething1 = 1;

    // Further clamp shadow quality to at least 0x16 (22)
    if (gShadowQuality < 0x16) {
        gShadowQuality = 0x16;
    }

    // Set flag 2
    gFlagSomething2 = 1;

    // Clamp texture quality to at most 0x16 (22)
    if (gTextureQuality > 0x16) {
        gTextureQuality = 0x16;
    }
}