// FUNC_NAME: DonControlManager::renderGadget
// Address: 0x0053df00
// Reconstructed C++ for EA EARS engine, The Godfather 2 (2008)
// This function renders a single gadget (UI element) from the don control system.
// It uses global arrays for active flags, render data, and texture info.

#include <cstdint>

// Global arrays (offsets known from binary analysis):
// g_elementActiveBase: base address 0x01198ecc, each element 0x1b bytes, first byte is active flag
// g_elementRenderDataBase: base address 0x01198ee4, each element 0x1b bytes, first 4 bytes is a pointer to render data
// g_textureDataArray: base address 0x011a0f28, each element 0x38 bytes, offsets +2 and +4 hold source width/height (uint16)
// g_globalElementIndex: address 0x0121bf30, holds the current element index to process
// g_screenWidth: address 0x00e2cd54, holds screen width used for scaling
// g_renderManager: address 0x0121be9c, pointer to rendering manager

static int g_globalElementIndex;       // DAT_0121bf30
static float g_screenWidth;            // DAT_00e2cd54 – assumed to be screen width
static void* g_renderManager;          // DAT_0121be9c – pointer to render manager

// Forward declarations of called functions (addresses from binary):
void FUN_006063b0(void);               // Pre‑render setup (e.g., clear/begin)
void FUN_0060add0(void* renderMgr, void* renderData, void* rectInfo); // Actual draw call

// Texture data structure (size 0x38 = 56 bytes)
#pragma pack(push, 1)
struct TextureData {
    uint8_t unknown0[2];               // offset 0
    uint16_t srcWidth;                 // offset 2
    uint16_t srcHeight;                // offset 4
    uint8_t unknown6[50];              // rest of structure
};
#pragma pack(pop)

// Rectangle structure passed to FUN_0060add0 (likely {int x, int y, float width, float height})
#pragma pack(push, 4)
struct RectF {
    int32_t x;          // offset 0
    int32_t y;          // offset 4
    float width;        // offset 8
    float height;       // offset 12
};
#pragma pack(pop)

// Main function
void DonControlManager::renderGadget(int textureIndex)  // textureIndex passed in ESI (unaff_ESI)
{
    // Check element active flag at g_elementActiveBase[g_globalElementIndex * 0x1b]
    uint8_t* activeFlag = reinterpret_cast<uint8_t*>(
        reinterpret_cast<uintptr_t>(g_elementActiveBase) + g_globalElementIndex * 0x1b);
    if (*activeFlag != 0) {
        // Perform pre‑render setup (e.g., reset state or begin UI pass)
        FUN_006063b0();
    }

    // Check render data pointer at g_elementRenderDataBase[g_globalElementIndex * 0x1b]
    void** renderDataPtr = reinterpret_cast<void**>(
        reinterpret_cast<uintptr_t>(g_elementRenderDataBase) + g_globalElementIndex * 0x1b);
    void* renderData = *renderDataPtr;
    if (renderData != nullptr) {
        // Prepare rectangle structure (x=0, y=0 initially)
        RectF rect;
        rect.x = 0;
        rect.y = 0;

        // Obtain texture data if textureIndex is within valid range (0x1000 = 4096)
        TextureData* texData = nullptr;
        if (textureIndex < 0x1000) {
            texData = reinterpret_cast<TextureData*>(
                reinterpret_cast<uintptr_t>(g_textureDataArray) + textureIndex * 0x38);
        }

        if (texData != nullptr) {
            // Compute scale factors: screenWidth divided by source width/height
            // These floats are used as width/height in the rect (possibly for UV or draw size)
            rect.width  = g_screenWidth / static_cast<float>(texData->srcWidth);
            rect.height = g_screenWidth / static_cast<float>(texData->srcHeight);
        } else {
            rect.width  = 0.0f;
            rect.height = 0.0f;
        }

        // Call the render function with the manager, render data, and rectangle info
        FUN_0060add0(g_renderManager, renderData, &rect);
    }
}