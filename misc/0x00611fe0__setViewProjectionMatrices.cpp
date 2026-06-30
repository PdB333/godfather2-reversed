// FUNC_NAME: setViewProjectionMatrices
// Function at 0x00611fe0 copies two 4x4 matrices from register arguments to global state,
// then updates a rendering context object with sub-matrices if present.

// Global matrices (0x40 bytes each = 16 floats)
extern float g_viewMatrix[16];       // _DAT_011f6640
extern float g_projectionMatrix[16]; // _DAT_011f6720

// Rendering context pointer
extern void* g_renderContext; // DAT_012058e8

// Internal helper functions (likely matrix multiply/assign)
void updateTransform(void* base, void* sub);   // FUN_0060b020
void updateSubTransform(void* base, void* sub);// FUN_0060aea0

// Parameters passed in ESI (viewMatrix) and EDI (projectionMatrix)
void __fastcall setViewProjectionMatrices(float* viewMatrix, float* projectionMatrix)
{
    // Copy view matrix to global
    for (int i = 0; i < 16; i++)
        g_viewMatrix[i] = viewMatrix[i];

    // Copy projection matrix to global
    for (int i = 0; i < 16; i++)
        g_projectionMatrix[i] = projectionMatrix[i];

    // Update rendering context if it exists (likely CameraManager or Renderer)
    if (g_renderContext != 0)
    {
        // Use group at +0x10 (e.g., view matrix group) with sub at +0x30
        if (*(int*)((char*)g_renderContext + 0x30) != 0)
            updateTransform(*(void**)((char*)g_renderContext + 0x10),
                            *(void**)((char*)g_renderContext + 0x30));

        // Use group at +0x14 (e.g., projection matrix group) with sub at +0x7c
        if (*(int*)((char*)g_renderContext + 0x7c) != 0)
            updateTransform(*(void**)((char*)g_renderContext + 0x14),
                            *(void**)((char*)g_renderContext + 0x7c));

        // Repeat for other sub-matrices (likely different transforms)
        if (*(int*)((char*)g_renderContext + 0x34) != 0)
            updateSubTransform(*(void**)((char*)g_renderContext + 0x10),
                               *(void**)((char*)g_renderContext + 0x34));

        if (*(int*)((char*)g_renderContext + 0x80) != 0)
            updateSubTransform(*(void**)((char*)g_renderContext + 0x14),
                               *(void**)((char*)g_renderContext + 0x80));

        if (*(int*)((char*)g_renderContext + 0x38) != 0)
            updateSubTransform(*(void**)((char*)g_renderContext + 0x10),
                               *(void**)((char*)g_renderContext + 0x38));

        if (*(int*)((char*)g_renderContext + 0x84) != 0)
            updateSubTransform(*(void**)((char*)g_renderContext + 0x14),
                               *(void**)((char*)g_renderContext + 0x84));
    }
    return;
}