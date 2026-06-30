// FUNC_NAME: QualityOptions::loadQualityOptions

#include <string.h>
#include <stdio.h>

// Forward declarations for helper functions (implemented elsewhere)
int readConfigInt(const char* key, int defaultValue);
int getDefaultConfigType();
void writeConfigInt(const char* key, int value);
unsigned char readConfigBool(const char* key, unsigned char defaultValue);

// Global configuration data – loaded from config system
static int g_configType;                   // DAT_00e50bc4
static unsigned char g_boolFlags[8];       // DAT_00e50be4 (8 bools: Bloom, HDR, SSAO, EdgeAA, DepthOfField?, ManipColor, ActorMotionBlur, Flare)
static unsigned char g_miscBools[8];       // DAT_00e50bec (first byte: ToneMapping, second: Decals, then ShaderQuality as int32 at +4)
static int g_shadowQuality;                // DAT_00e50bf4 (0-3? or 0-5?)

// "Applied" copy – contains the currently active quality settings
static unsigned long long g_activeBoolFlags; // DAT_00e50bd0 (packed representation of g_boolFlags)
static unsigned long long g_activeMiscBools; // DAT_00e50bd8 (packed representation of g_miscBools)
static int g_activeConfigType;             // DAT_00e50bcc
static int g_activeShadowQuality;          // DAT_00e50be0

void QualityOptions::loadQualityOptions(bool applyImmediately)
{
    char key[1024];  // local_400
    // Extra buffer (probably padding/alignment, not used)
    // unsigned char unused[1023];
    // memset(unused, 0, sizeof(unused));

    key[0] = '\0';

    // Load config type (defaults to 0 if missing)
    g_configType = readConfigInt("QualityOptions.ConfigType", 0);
    if (g_configType == 0) {
        g_configType = getDefaultConfigType();
        writeConfigInt("QualityOptions.ConfigType", g_configType);
    }

    // Option names (pointers to string literals in the original binary)
    static const char* optionNames[] = {
        "Bloom",        // PTR_s_Bloom_00e50b94
        "HDR",          // PTR_DAT_00e50b98
        "SSAO",         // PTR_DAT_00e50b9c
        "EdgeAA",       // PTR_s_EdgeAA_00e50ba0
        "DepthOfField", // PTR_DAT_00e50ba4 (inferred)
        "ManipColor",   // PTR_s_ManipColor_00e50ba8
        "ActorMotionBlur", // PTR_s_ActorMotionBlur_00e50bac
        "Flare"         // PTR_s_Flare_00e50bb0
    };

    for (int i = 0; i < 8; i++) {
        snprintf(key, sizeof(key), "QualityOptions.%s", optionNames[i]);
        g_boolFlags[i] = readConfigBool(key, g_boolFlags[i]);
    }

    // ToneMapping (first byte of second structure)
    snprintf(key, sizeof(key), "QualityOptions.%s", "ToneMapping"); // PTR_s_ToneMapping_00e50bb4
    g_miscBools[0] = readConfigBool(key, g_miscBools[0]);

    // Decals (second byte)
    snprintf(key, sizeof(key), "QualityOptions.%s", "Decals"); // PTR_s_Decals_00e50bb8
    g_miscBools[1] = readConfigBool(key, g_miscBools[1]);

    // ShaderQuality (4-byte integer, stored at offset 4 in g_miscBools)
    snprintf(key, sizeof(key), "QualityOptions.%s", "ShaderQuality"); // PTR_s_ShaderQuality_00e50bbc
    *(int*)(g_miscBools + 4) = readConfigInt(key, *(int*)(g_miscBools + 4));

    // Shadows (4-byte integer)
    snprintf(key, sizeof(key), "QualityOptions.%s", "Shadows"); // PTR_s_Shadows_00e50bc0
    g_shadowQuality = readConfigInt(key, g_shadowQuality);

    // If requested, copy all loaded values to the "active" set
    if (applyImmediately) {
        // Pack the 8 boolean flags into a single 64-bit value
        g_activeBoolFlags = 0;
        for (int i = 0; i < 8; i++) {
            g_activeBoolFlags |= ((unsigned long long)g_boolFlags[i]) << (i * 8);
        }

        // Pack the misc booleans (first 2 bytes) and shader quality (next 4 bytes)
        // This matches the CONCAT operations in the original code
        g_activeMiscBools = ((unsigned long long)g_miscBools[0]) |
                            ((unsigned long long)g_miscBools[1] << 8) |
                            ((unsigned long long)(*(unsigned int*)(g_miscBools + 4)) << 16);

        g_activeConfigType = g_configType;
        g_activeShadowQuality = g_shadowQuality;
    }
}