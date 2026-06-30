// FUNC_NAME: ScreenTexture::reinitialize
// Function address: 0x005db5c0
// Reinitializes the screen texture when dimensions change, allocates buffer and creates D3D texture.

#include <cstdint>

// Forward declarations
extern int g_screenWidth;        // DAT_012056b4
extern int g_screenHeight;       // DAT_012056b8
extern int g_textureIdCounter;   // DAT_0103ae2c
extern void* (*g_alloc)(uint32_t size, int flags);   // DAT_0119caf0
extern void (*g_free)(void* ptr);                     // DAT_0119caf4

// Global render resource manager (DAT_01206880) - assumed structure
struct RenderResourceManager {
    // +0x14: dynamic buffer for texture creation commands
    uint32_t* commandBuffer;
    uint32_t commandBufferSize;
};
extern RenderResourceManager* g_renderMgr;

// Unknown external texture creation function
// Returns handle? Probably creates a D3D texture
int createTexture(int type, uint32_t flags, int width, int height, int mipLevels, int format); // FUN_00606c80

class ScreenTexture {
public:
    // Offsets relative to this pointer
    int width;                 // +0x04
    int height;                // +0x08
    int unknownId;             // +0x0C (set to 0)
    int textureId;             // +0x10 (also from counter)
    int bufferId;              // +0x14 (from counter)
    void* buffer;              // +0x18
    uint32_t bufferSize;       // +0x1C
    int anotherId;             // +0x20 (from counter)

    void reinitialize(int bitsPerPixel);
};

void ScreenTexture::reinitialize(int bitsPerPixel) {
    // Check if global screen dimensions are valid and different from current
    if (g_screenWidth != 0 && g_screenHeight != 0) {
        bool needsUpdate = (textureId == 0); // If texture ID is 0, always update
        if (textureId != 0) {
            needsUpdate = (width != g_screenWidth) || (height != g_screenHeight);
        }

        if (needsUpdate) {
            // Update dimensions
            width = g_screenWidth;
            height = g_screenHeight;

            // Free existing buffer if any
            if (buffer != nullptr) {
                g_free(buffer);
                buffer = nullptr;
            }

            // Calculate buffer size: width * height * bitsPerPixel / 8
            bufferSize = (uint32_t)(width * height * bitsPerPixel) >> 3;
            buffer = g_alloc(bufferSize, 0); // Allocate buffer

            // Assign IDs from global counter (ensuring unique)
            if (bufferId == 0) {
                bufferId = ++g_textureIdCounter;
            }
            unknownId = 0; // Reset unknown field

            if (anotherId == 0) {
                anotherId = ++g_textureIdCounter;
            }

            if (textureId == 0) {
                textureId = ++g_textureIdCounter;
            }

            // Create the D3D texture via external function
            int textureHandle = createTexture(9, 0x200000, width, height, 1, 0xFFFFFFFF);

            // Record texture creation command in global render manager's command buffer
            // Each entry: 4 integers (command type?, textureId, anotherId, handle)
            uint32_t* cmd = &g_renderMgr->commandBuffer[g_renderMgr->commandBufferSize];
            *cmd = reinterpret_cast<uint32_t>(&PTR_LAB_011273a4); // Some vtable or identifier
            cmd++;
            *cmd = static_cast<uint32_t>(anotherId);
            cmd++;
            *cmd = static_cast<uint32_t>(textureId);
            cmd++;
            *cmd = static_cast<uint32_t>(textureHandle);
            cmd++;
            g_renderMgr->commandBufferSize += 4; // Increment by 4 words
        }
    }
}