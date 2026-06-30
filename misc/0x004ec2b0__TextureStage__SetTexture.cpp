// FUNC_NAME: TextureStage::SetTexture
// Address: 0x004ec2b0
// Role: Sets the texture state for a render target stage. Manages reference counting, allocation, and binds the texture to the target.

// Constants and forward declarations
extern const unsigned int DefaultColor; // DAT_00e2b1a4 - likely 0xFFFFFFFF (white) or 1.0f
extern void* TextureState_vtable; // PTR_FUN_00e372b4

// Forward declarations of called functions
void ApplyTexture(int stageIndex); // FUN_004ec1c0
void* AllocateMemory(int size, int type, int alignment, int flags); // wrapper for allocator

// Internal structures
struct TextureState {
    void** vtable;     // +0x00
    int refCount;      // +0x04
    int field_08;      // +0x08 (unknown, initialized to 0)
    unsigned int r;    // +0x10
    unsigned int g;    // +0x14
    unsigned int b;    // +0x18
    unsigned int a;    // +0x1c
};

struct RenderTarget { // placeholder for object at this+0x10
    // +0x20: TextureState* m_pTextureSlot (the stage texture)
    TextureState* m_pTextureSlot;
};

// This class defines offsets used in this function
class TextureStage {
public:
    RenderTarget* m_pRenderTarget; // +0x10
    TextureState* m_pTexture;      // +0x14 (current texture state)

    void SetTexture(int stageIndex);
};

void TextureStage::SetTexture(int stageIndex) {
    // Release old texture if present
    if (m_pRenderTarget != 0) {
        if (m_pTexture != 0) {
            m_pTexture->refCount--;
            if (m_pTexture->refCount == 0) {
                // Call destructor via vtable offset 4
                (*(void (__thiscall**)())(m_pTexture->vtable[1]))();
            }
            m_pTexture = 0;
        }

        // Allocate new TextureState via custom allocator
        // Allocator parameters: size=0x30, type=2, alignment=0x10, flags=0
        int allocParams[3] = {2, 0x10, 0};
        void* allocatorPtr = FUN_009c8f80(); // returns pointer to allocator vtbl
        TextureState* newTex = (TextureState*)(*(void* (__thiscall**)(int, int*))allocatorPtr)(0x30, allocParams);

        if (newTex != 0) {
            newTex->refCount = 0;
            newTex->vtable = &TextureState_vtable;
            newTex->field_08 = 0;
            newTex->r = DefaultColor;
            newTex->g = DefaultColor;
            newTex->b = DefaultColor;
            newTex->a = DefaultColor;
        }
        m_pTexture = newTex;

        // Apply texture stage (e.g., update hardware state)
        ApplyTexture(stageIndex);

        // Override color values after apply (possibly reset to default)
        if (newTex != 0) {
            newTex->r = DefaultColor;
            newTex->g = DefaultColor;
            newTex->b = DefaultColor;
            newTex->a = DefaultColor;
        }

        // Bind the new texture to the render target's texture slot
        if (m_pRenderTarget->m_pTextureSlot != 0) {
            m_pRenderTarget->m_pTextureSlot->refCount--;
            if (m_pRenderTarget->m_pTextureSlot->refCount == 0) {
                (*(void (__thiscall**)())(m_pRenderTarget->m_pTextureSlot->vtable[1]))();
            }
        }
        m_pRenderTarget->m_pTextureSlot = newTex;
        if (newTex != 0) {
            newTex->refCount++;
        }

        // Add an extra reference for the TextureStage itself
        if (m_pTexture != 0) {
            m_pTexture->refCount++;
        }
    }
}