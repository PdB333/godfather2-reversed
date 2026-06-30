// FUNC_NAME: FontTextureLoader::LoadGlyphTextures
// Address: 0x004e1dd0
// Role: Loads glyph textures for a font atlas, processing a predefined glyph table and creating texture handles for each glyph.

#include <cstdint>

// Constants from the game binary
constexpr uint32_t MAX_FONTS = 256; // guess
constexpr uint32_t MAX_GLYPH_TABLE_ENTRIES = 512; // guess
constexpr uint32_t MAX_TEXTURE_SLOTS = 0x1000; // 4096, used for texture handle range
constexpr uint32_t GLYPH_DATA_STRIDE = 0x56; // 86 bytes per font glyph data

// Global variables (exported from binary symbols)
static int32_t g_fontCount;               // DAT_012054d8
static uint8_t g_fontGlyphData[MAX_FONTS * GLYPH_DATA_STRIDE]; // DAT_01194558
// This array is used as a pool of texture info structures (each 0x38 = 56 bytes)
static uint8_t g_textureInfoPool[MAX_TEXTURE_SLOTS * 0x38]; // DAT_011a0f28
// Glyph table at DAT_00e2ddc2, each entry 8 bytes
static const uint8_t g_glyphTable[]; // DAT_00e2ddc2
// Some constant ratio (maybe 1.0f / 100.0f or similar)
static const float g_aspectBase = 1.0f; // DAT_00e2b1a4

// Forward declarations of sub-functions (callees)
bool GetFontSlot(int32_t& slot, int32_t width);           // 0x004e1d80
int32_t GetDiffuseTextureType();                           // 0x004e3a30
int32_t GetSpecularTextureType();                          // 0x004e3a50
uint8_t* GetTextureData(int32_t handle);                   // 0x00606370, returns pointer to texture info
uint32_t AllocateTextureSlot();                            // 0x00606b50
uint32_t CreateTexture(int32_t type, uint32_t flags, uint16_t width, uint16_t height,
                       uint8_t mipCount, uint32_t parentHandle); // 0x00606c80
bool CheckTextureFormatSupported();                       // 0x00608210

//-----------------------------------------------------------------------------
// Load glyph textures for a font atlas of given width/height.
// Returns the font slot index on success, or -1 on failure.
//-----------------------------------------------------------------------------
int32_t FontTextureLoader::LoadGlyphTextures(int32_t textureWidth, int32_t textureHeight)
{
    int32_t fontSlot; // will be set by GetFontSlot

    // Check if we can allocate a new font slot (maybe capacity check)
    if (!GetFontSlot(&fontSlot, textureWidth))
    {
        // Failed to get a slot; function returns whatever GetFontSlot stored (likely error code)
        return fontSlot;
    }

    // Acquire the font slot index and initialize the glyph data structure
    fontSlot = g_fontCount++;
    uint8_t* fontGlyphPtr = &g_fontGlyphData[fontSlot * GLYPH_DATA_STRIDE];

    // Compute aspect ratios based on texture dimensions
    float widthRatio = g_aspectBase / static_cast<float>(textureWidth);
    float heightRatio = g_aspectBase / static_cast<float>(textureHeight);

    // Store base glyph data: width, height, ratios
    *reinterpret_cast<int16_t*>(fontGlyphPtr + 0x00) = static_cast<int16_t>(textureWidth);
    *reinterpret_cast<int16_t*>(fontGlyphPtr + 0x02) = static_cast<int16_t>(textureHeight);
    *reinterpret_cast<float*>(fontGlyphPtr + 0x04) = widthRatio;
    *reinterpret_cast<float*>(fontGlyphPtr + 0x08) = heightRatio;

    // Zero out the texture handle array in this glyph data (20 entries, each 4 bytes, stride 8? Actually loop increments by 8 but writes 4 bytes each)
    // From code: puVar3 = &DAT_01194564 + iVar6 * 0x2b; iVar6 = 0x14; do { *puVar3 = 0; puVar3 += 2; iVar6--; } while (iVar6 != 0);
    // This clears the handle array starting at offset 0x0C (since 0x04+0x08=0x0C) maybe.
    uint32_t* handleArray = reinterpret_cast<uint32_t*>(fontGlyphPtr + 0x0C);
    for (int i = 0; i < 20; ++i)
    {
        handleArray[i] = 0;
    }

    // Process the glyph table (8-byte entries)
    const uint8_t* tablePtr = g_glyphTable; // starts at DAT_00e2ddc2
    while (reinterpret_cast<uintptr_t>(tablePtr) < 0x00e2df02) // end address
    {
        // Each glyph table entry (8 bytes):
        // byte -1: glyph index (char code)
        // byte  0-1: short glyphWidth (or scaled)
        // byte  2-3: short glyphHeight
        // byte  4: type
        // byte  5: flags
        // byte  6: targetSlot (index into another glyph's handle array)
        // byte  7: padding

        uint8_t glyphIndex = tablePtr[-1]; // local_4
        int16_t origGlyphWidth  = *reinterpret_cast<const int16_t*>(tablePtr);     // sVar1 from *local_10
        int16_t origGlyphHeight = *reinterpret_cast<const int16_t*>(tablePtr + 2); // sVar1 from local_10[1]
        uint8_t type = tablePtr[4];   // local_10[2]
        uint8_t flags = tablePtr[5];  // local_10[3]
        int8_t targetSlot = static_cast<int8_t>(tablePtr[6]); // local_10+5

        // Determine texture size (maybe scaling)
        int32_t width = textureWidth;
        int32_t height = textureHeight;

        uint8_t mipLevel = 4; // initial value (local_14)

        // If flag bit 0 (0x01) is set, compute power-of-two size and determine mip level
        if ((flags & 0x03) != 0)
        {
            // Round up to next power of two
            if (textureWidth > 0)
            {
                int pow = 1;
                while (pow <= textureWidth)
                    pow <<= 1;
                width = pow >> 1;
            }
            if (textureHeight > 0)
            {
                int pow = 1;
                while (pow <= textureHeight)
                    pow <<= 1;
                height = pow >> 1;
            }

            // Use the smaller of the two dimensions
            int dim = (height <= width) ? height : width;

            // Compute mip level: number of right-shifts until dimension <= 32 (0x20)
            mipLevel = 0;
            while (dim > 32)
            {
                dim >>= 1;
                ++mipLevel;
            }
        }

        // Compute effective glyph width and height (handle negative values as divisions)
        int32_t glyphWidth = origGlyphWidth;
        int32_t glyphHeight = origGlyphHeight;

        if (origGlyphWidth < 0)
            glyphWidth = -(width / -origGlyphWidth); // division when negative? Actually code: uVar8 = -(iVar6 / (int)local_18); then if uVar8 < 1 set to 1 else if negative recalc
        if (glyphWidth < 1)
            glyphWidth = 1;
        if (origGlyphWidth < 0)
            glyphWidth = -(width / -origGlyphWidth); // duplicate? simplification: treat as division

        if (origGlyphHeight < 0)
            glyphHeight = -(height / -origGlyphHeight);
        if (glyphHeight < 1)
            glyphHeight = 1;
        if (origGlyphHeight < 0)
            glyphHeight = -(height / -origGlyphHeight);

        // Determine texture type based on the glyph type
        int32_t textureType;
        switch (type)
        {
        case 0:  textureType = GetDiffuseTextureType(); break;
        case 1:  textureType = GetSpecularTextureType(); break;
        case 3:  textureType = 0x1D; break;
        case 4:  textureType = 0x15; break;
        default: textureType = 3; break;
        }

        // Build flags
        // Base flags: 0x40200098; if type != 0x15, add 0x10000
        uint32_t flagsVal = 0x40200098;
        if (textureType != 0x15)
            flagsVal |= 0x10000;

        // If flag bit 1 (0x02) not set, force mip count to 1
        if ((flags & 0x02) == 0)
            mipLevel = 1;
        else if (mipLevel > 1)
            flagsVal |= 0x01; // set bit 0 in flags? Actually code: uVar9 = uVar8 | 0x40200099; so increment lowest nibble by 1.

        // Determine parent handle (subtexture from existing glyph)
        uint32_t parentHandle = 0xFFFFFFFF; // default: independent texture
        if (targetSlot != -1)
        {
            // Get the existing texture handle from the glyph data at the target slot
            uint32_t existingHandle = *reinterpret_cast<uint32_t*>(&g_fontGlyphData[fontSlot * GLYPH_DATA_STRIDE + 0x06 + targetSlot * 4]);
            // Check if the existing texture can accommodate the requested size
            uint8_t* textureInfo;
            if (existingHandle < MAX_TEXTURE_SLOTS)
                textureInfo = &g_textureInfoPool[existingHandle * 0x38];
            else
                textureInfo = nullptr;

            if (textureInfo)
            {
                uint16_t existingWidth  = *reinterpret_cast<uint16_t*>(textureInfo + 2);
                uint16_t existingHeight = *reinterpret_cast<uint16_t*>(textureInfo + 4);
                if (existingWidth >= glyphWidth && existingHeight >= glyphHeight)
                {
                    // Allocate a new texture slot (for sub-texture)
                    uint32_t newHandle = AllocateTextureSlot();
                    if (newHandle < MAX_TEXTURE_SLOTS)
                    {
                        uint8_t* newInfo = &g_textureInfoPool[newHandle * 0x38];
                        uint8_t refCount = *newInfo; // first byte is reference count?
                        if (refCount <= 1)
                        {
                            // Optionally adjust mip level from the target texture info
                            if (mipLevel == 0)
                                mipLevel = *(newInfo + 1); // second byte maybe original mip?
                            parentHandle = newHandle;
                        }
                        else
                        {
                            parentHandle = 0xFFFFFFFF; // fall back to independent texture
                        }
                    }
                    else
                    {
                        parentHandle = 0xFFFFFFFF;
                    }
                }
                else
                {
                    // Cannot fit; skip this glyph (assign -1)
                    parentHandle = 0xFFFFFFFF;
                }
            }
            else
            {
                // Invalid existing handle
                parentHandle = 0xFFFFFFFF;
            }
        }

        // Create the texture (or sub-texture)
        uint32_t newTextureHandle = CreateTexture(textureType, flagsVal, static_cast<uint16_t>(glyphWidth),
                                                  static_cast<uint16_t>(glyphHeight), mipLevel, parentHandle);

        // Store the generated handle in the glyph data array at the glyph's index
        *reinterpret_cast<uint32_t*>(&g_fontGlyphData[fontSlot * GLYPH_DATA_STRIDE + 0x06 + glyphIndex * 4]) = newTextureHandle;

        // After creating, for certain texture types (0x18..0x1d) if hardware doesn't support the format,
        // create a fallback 0x15 texture and store it in the texture info's +0x1c field.
        // This uses a "recent" texture handle (extraout_ECX) which is unclear from decompilation.
        // We'll assume it's the same as newTextureHandle (the one just created).
        if ((textureType >= 0x18 && textureType <= 0x1d) && !CheckTextureFormatSupported())
        {
            uint32_t recentHandle = newTextureHandle; // approximate
            if (recentHandle < MAX_TEXTURE_SLOTS)
            {
                uint8_t* texInfo = &g_textureInfoPool[recentHandle * 0x38];
                // Check if fallback texture already exists at offset +0x1c
                if (*reinterpret_cast<uint32_t*>(texInfo + 0x1c) == 0)
                {
                    uint32_t fallbackHandle = CreateTexture(0x15,
                                                             *reinterpret_cast<uint32_t*>(texInfo + 0x0c),
                                                             *reinterpret_cast<uint16_t*>(texInfo + 2),
                                                             *reinterpret_cast<uint16_t*>(texInfo + 4),
                                                             *(texInfo + 1),
                                                             0xFFFFFFFF);
                    *reinterpret_cast<uint32_t*>(texInfo + 0x1c) = fallbackHandle;
                }
            }
        }

        // Advance to next glyph table entry (8 bytes)
        tablePtr += 8;
    }

    return fontSlot;
}