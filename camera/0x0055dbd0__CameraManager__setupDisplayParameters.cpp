// FUNC_NAME: CameraManager::setupDisplayParameters
#include <cstdint>

// Note: This function is approximately at 0x55dbd0.
// It uses this+0x18 as a pointer to a rendering subsystem, then calls two virtual methods (offsets 0x40 and 0x44)
// on two small parameter blocks constructed from global constants (screen dimensions?).
// The two blocks likely represent viewport or projection setups for different render passes (e.g., main scene and UI).

struct ViewportParams {
    float x0;      // 0x0
    float y0;      // 0x4
    float x1;      // 0x8
    float y1;      // 0xC
};

class CameraManager {
public:
    // +0x18: pointer to rendering subsystem (e.g., RenderDevice)
    uint8_t* m_renderDevice; // offset 0x18, not shown below.

    // +0xd0 from renderDevice: pointer to a viewport manager or context
    // +0x40 and +0x44 are virtual function indices on that manager.

    void setupDisplayParameters() {
        // First viewport block (e.g., main camera)
        ViewportParams viewport1;
        viewport1.x0 = 0.0f;
        viewport1.y0 = *(float*)0x00e44754; // DAT_00e44754: likely screen height or a vertical offset
        viewport1.x1 = 0.0f;
        viewport1.y1 = *(float*)0x00e2b1a4; // DAT_00e2b1a4: likely screen width or a horizontal offset

        FUN_009f2000(); // Unknown init / sync function

        // ++0xd0 from renderDevice is a pointer to a viewport handler
        uint8_t* viewportHandler = *(uint8_t**)(*(uint32_t*)(m_renderDevice + 0xd0));
        // Call virtual method at offset 0x40 (e.g., setViewport) with pointer to viewport1
        (**(void (**)(void*, ViewportParams*))(*(uint32_t*)viewportHandler + 0x40))(viewportHandler, &viewport1);

        // Second viewport block (e.g., UI or reflection)
        ViewportParams viewport2;
        viewport2.x0 = 0.0f;
        viewport2.y0 = 0.0f;
        viewport2.x1 = 0.0f;
        viewport2.y1 = *(float*)0x00e2b1a4; // Same global as before (screen width?)

        FUN_009f2000(); // Another sync

        // Call virtual method at offset 0x44 (e.g., setScissorRect)
        (**(void (**)(void*, ViewportParams*))(*(uint32_t*)viewportHandler + 0x44))(viewportHandler, &viewport2);
    }
};