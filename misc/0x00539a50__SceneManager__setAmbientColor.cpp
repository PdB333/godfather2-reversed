// FUNC_NAME: SceneManager::setAmbientColor
// Address: 0x00539a50
// This function sets the ambient color for the scene (4 floats: RGBA or XYZW).
// It only applies the color if the global scene manager is initialized,
// a specific flag is set, and a slot index points to a valid entry.
struct ColorRGBA {
    float r, g, b, a; // or x, y, z, w depending on usage
};

// Global scene manager state (base at 0x0121b740)
extern SceneManager* g_pActiveSceneManager; // DAT_012058e8, pointer to active scene manager instance
extern uint8_t g_sceneManagerBuffer[0x200]; // DAT_0121b740, static allocation
// Offsets within the buffer:
// +0x14: some float? (DAT_0121b754)
// +0x110: ambient color (DAT_0121b850)
// +0x134: enable flag? (DAT_0121b874)
// +0x138: index into an array (DAT_0121b878)
// +0x2D4: array of pointers (DAT_0121ba14)

// External function that applies the color to the renderer
void __fastcall applySceneAmbientColor(float arg1, float* color); // FUN_0060add0

void __fastcall setSceneAmbientColor(const ColorRGBA* color)
{
    // Write the 16-byte color to the global scene buffer at offset 0x110
    *(uint32_t*)(&g_sceneManagerBuffer[0x110]) = *(uint32_t*)&color->r;
    *(uint32_t*)(&g_sceneManagerBuffer[0x114]) = *(uint32_t*)&color->g;
    *(uint32_t*)(&g_sceneManagerBuffer[0x118]) = *(uint32_t*)&color->b;
    *(uint32_t*)(&g_sceneManagerBuffer[0x11C]) = *(uint32_t*)&color->a;

    // Check if the global active scene manager points to this buffer AND the enable flag is set AND the slot is valid
    if ((g_pActiveSceneManager == (SceneManager*)&g_sceneManagerBuffer) &&
        (*(uint32_t*)(&g_sceneManagerBuffer[0x134]) != 0) &&
        (*(void**)(&g_sceneManagerBuffer[0x2D4] + *(uint32_t*)(&g_sceneManagerBuffer[0x138]) * 4) != 0))
    {
        applySceneAmbientColor(
            *(float*)(&g_sceneManagerBuffer[0x14]),                              // Some parameter (maybe time or blend factor)
            *(float**)(&g_sceneManagerBuffer[0x2D4] + *(uint32_t*)(&g_sceneManagerBuffer[0x138]) * 4), // Pointer from the array
            &g_sceneManagerBuffer[0x110]                                         // The just-written color
        );
    }
}