// FUNC_NAME: Presentation::setGlobalShaderConstants
// Address: 0x00535320
// Role: Copies a block of 16 floats (shader constants) into global storage and applies them to the current material/texture slots.

// Global variables
extern float gShaderConstants[16]; // 0x01219b90 - 0x01219bcc (4 bytes each)
extern char gShaderFlag;            // 0x01219b38
extern void* gRenderDevice;         // 0x012058e8
extern void* gBaseAddress;          // 0x01219a70
extern int gCurrentMaterialSlot;    // 0x01219b20 (index into material array with stride 0x30)
extern int gCurrentTextureSlot;     // 0x01219b21 (index into texture array with stride 0x3c)
extern void* gMaterialData;         // 0x01219a80 (device context for materials)
extern void* gTextureData;          // 0x01219a84 (device context for textures)

// Arrays of material and texture handles (stride 0x30 = 48 bytes, 0x3c = 60 bytes)
extern int gMaterialArray[];        // starts at 0x01219cc4
extern int gTextureArray[];         // starts at 0x01219d70 (alternate indexing?)
extern int gTextureAltArray[];      // starts at 0x01219cd8 (another array)

// External functions
void setShaderConstant(void* device, int handle, float* data);  // FUN_0060b020
void setShaderTexture(void* device, int handle, void* data);    // FUN_0060add0

// Known global texture data pointers (probably pre-defined color textures)
extern void* gTextureColorWhite;     // 0x011280d0
extern void* gTextureColorBlack;     // 0x00e2e770 (used when flag is 0)
extern void* gTextureDefault1;       // 0x01163810
extern void* gTextureDefault2;       // 0x00e2e760
extern void* gTextureDefault3;       // 0x011637d0
extern void* gTextureDefault4;       // 0x00e2e720
extern char gTextureFlag;            // 0x01163840 (determines which default texture to use)

void __thiscall Presentation::setGlobalShaderConstants(float* constantData, char flag)
{
    // Copy the 16 floats into global shader constants
    for (int i = 0; i < 16; i++)
    {
        gShaderConstants[i] = constantData[i];
    }
    // Store the flag
    gShaderFlag = flag;

    // Apply to the current material/texture slots if the renderer is active
    if (gRenderDevice == gBaseAddress)
    {
        // Material slot 1 (stride 0x30, index from gCurrentMaterialSlot)
        int materialHandle1 = gMaterialArray[gCurrentMaterialSlot * (0x30 / 4)]; // each element is 4 bytes? Actually stride in bytes, so divide by sizeof(int)
        if (materialHandle1 != 0)
        {
            setShaderConstant(gMaterialData, materialHandle1, constantData);
        }

        // Material slot 2: texture assignment
        int textureHandle1 = gTextureAltArray[gCurrentMaterialSlot * (0x30 / 4)];
        if (textureHandle1 != 0)
        {
            void* textureData = gTextureColorWhite;
            if (flag == 0)
            {
                textureData = gTextureColorBlack;
            }
            setShaderTexture(gMaterialData, textureHandle1, textureData);
        }

        // Texture slot (stride 0x3c, index from gCurrentTextureSlot)
        int textureHandle2 = gMaterialArray[gCurrentTextureSlot * (0x3c / 4)]; // actually gMaterialArray? No, different base: &DAT_01219d70
        if (textureHandle2 != 0)
        {
            void* textureData = gTextureDefault1;
            if (gTextureFlag == 0)
            {
                textureData = gTextureDefault2;
            }
            // Note: uses gTextureData for device context
            setShaderTexture(gTextureData, textureHandle2, textureData);
        }

        // Another texture assignment for the same slot?
        int textureHandle3 = gTextureAltArray[gCurrentTextureSlot * (0x3c / 4)]; // &DAT_01219d74
        if (textureHandle3 != 0)
        {
            void* textureData = gTextureDefault3;
            if (gTextureFlag == 0)
            {
                textureData = gTextureDefault4;
            }
            // Note: uses setShaderConstant (not setShaderTexture) - likely a constant instead
            setShaderConstant(gTextureData, textureHandle3, textureData);
        }
    }
}