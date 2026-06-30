// FUNC_NAME: SpriteRenderer::drawSpriteWithTransform
// Address: 0x00769060
// Role: Renders a sprite after setting up a transform, checking culling state.

#include <cstdint>

// Forward declarations for called functions (not defined here)
// These functions are part of the EA EARS rendering system.
void transformSetTransform(uint32_t param, float x, float y, float z);
void transformPush();
bool isTransformDirty(); // Returns true if transform needs to be recalculated
void* getTextureData(uint32_t handle); // Gets texture data from resource handle
void* getRenderHandle(void* textureData); // Converts to renderable handle (e.g., texture ID)

class SpriteRenderer {
public:
    // Virtual function table entry at +0x2C
    virtual void drawSprite(void* renderHandle, int blendMode, int flag1, int flag2, float colorR, float colorG) = 0;
};

// Global constants for identity transform (likely from .data section)
extern const float _DAT_00d65bd4; // = 1.0f? (scale/rotation component)
extern const float _DAT_00d65bd8; // = 0.0f? (translation x)
extern const float _DAT_00d65bdc; // = 0.0f? (translation y)

void __thiscall SpriteRenderer::drawSpriteWithTransform(int* thisPtr, uint32_t transformHandle, uint32_t spriteHandle)
{
    // Set the transform to identity using constant values
    transformSetTransform(transformHandle, _DAT_00d65bd4, _DAT_00d65bd8, _DAT_00d65bdc);
    
    // Push the current transform state onto the stack
    transformPush();
    
    // Check if the transform is dirty or culled – skip rendering if not needed
    if (!isTransformDirty()) {
        void* textureData = getTextureData(spriteHandle);
        void* renderHandle = getRenderHandle(textureData);
        
        // Call the virtual draw function with blend mode 1, flags 0,0, and white color (1.0f)
        (thisPtr->*vtable[0x2c / 4])(renderHandle, 1, 0, 0, 1.0f, 1.0f);
    }
}