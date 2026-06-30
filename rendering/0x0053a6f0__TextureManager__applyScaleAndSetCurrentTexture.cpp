// FUNC_NAME: TextureManager::applyScaleAndSetCurrentTexture
// Address: 0x0053a6f0
// Role: Sets the current texture index and applies scaling factors based on texture dimensions and a base scale.
//       Also calls helper functions if certain global conditions are met.

#include <cstdint>

// Forward declarations of called functions
void someFunction1(void);
void someFunction2(uint32_t param1, void* param2, int32_t* dimensionsOut);

// Global variables (from Ghidra data references)
static uint32_t g_currentTextureIndex;                          // DAT_0121b990
static void* g_pManagerSingleton;                               // DAT_012058e8
static void* g_someManagerInstance;                             // DAT_0121b740 (address used for comparison)
static uint32_t g_screenWidth;                                  // DAT_0121b754
static uint32_t g_textureAtlasWidth;                            // DAT_0121bbd0
static uint32_t g_bSomeFlag;                                    // DAT_0121bba0
static void* g_pSomePointer;                                    // DAT_0121bba4
static float g_baseScale;                                       // DAT_00e2cd54

// Texture descriptor table (0x38 bytes per entry, at 0x011a0f28)
struct TextureDescriptor {
    uint16_t unknown0;   // offset +0
    uint16_t width;      // offset +2
    uint16_t height;     // offset +4
    // remaining bytes up to 0x38 are unknown
};
static TextureDescriptor g_textureDescriptorTable[0x1000];      // DAT_011a0f28

void TextureManager::applyScaleAndSetCurrentTexture(uint32_t textureIndex)
{
    g_currentTextureIndex = textureIndex;

    // Check that the manager singleton points to a specific instance and screen width matches atlas width
    if (g_pManagerSingleton == &g_someManagerInstance && g_screenWidth == g_textureAtlasWidth)
    {
        if (g_bSomeFlag)
        {
            someFunction1();
        }

        if (g_pSomePointer)
        {
            int32_t dimensions[2] = {0, 0};   // local_20, local_1c

            TextureDescriptor* pDesc = nullptr;
            if (textureIndex < 0x1000)
            {
                pDesc = &g_textureDescriptorTable[textureIndex];
            }

            // Compute scale factors: base scale divided by texture dimensions
            float scaleX = g_baseScale / static_cast<float>(pDesc->width);
            float scaleY = g_baseScale / static_cast<float>(pDesc->height);

            someFunction2(g_screenWidth, g_pSomePointer, dimensions);
        }
    }
}