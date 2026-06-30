// FUNC_NAME: setRenderTargetScale
// Address: 0x0053c250
// Role: Sets up render target scaling factors based on current surface dimensions and a scale parameter.
// Calls FUN_0060add0 to apply the scaling.

struct SurfaceInfo {
    uint16_t width;   // +0x02
    uint16_t height;  // +0x04
    // ... other fields (size 0x38 total)
};

// Global state (likely part of a renderer singleton)
extern uint32_t g_currentRenderTarget;   // DAT_01125ab4
extern uint32_t g_someOtherTarget;       // DAT_01125b44
extern uint32_t g_currentSurfaceIndex;   // DAT_01125b80
extern float g_scaleX;                   // DAT_01125b70
extern float g_scaleY;                   // DAT_01125b74
extern uint32_t g_renderTargetId;        // DAT_01125b78
extern uint32_t g_someId;                // DAT_01125b7c
extern uint32_t g_someIdA;               // DAT_01125b58
extern uint32_t g_someIdB;               // DAT_01125b64
extern float g_baseScale;                // DAT_00e2b1a4
extern SurfaceInfo g_surfaceArray[4096]; // DAT_011a0f28 (max 0x1000 entries)

void setRenderTargetScale(uint32_t renderTargetId, float scale, uint32_t someId) {
    SurfaceInfo* surface;
    uint32_t uVar2;

    if (g_currentRenderTarget == g_someOtherTarget) {
        // Use constant base scale when targets match
        surface = (g_currentSurfaceIndex < 0x1000) ? &g_surfaceArray[g_currentSurfaceIndex] : nullptr;
        g_scaleX = g_baseScale / (float)surface->width;
        g_scaleY = g_baseScale / (float)surface->height;
        someId = 0;
        uVar2 = g_someIdA;
    } else {
        // Use provided scale parameter
        surface = (g_currentSurfaceIndex < 0x1000) ? &g_surfaceArray[g_currentSurfaceIndex] : nullptr;
        g_scaleX = scale / (float)surface->width;
        g_scaleY = scale / (float)surface->height;
        uVar2 = g_someIdB;
    }

    g_renderTargetId = renderTargetId;
    g_someId = someId;

    // Apply scaling (function takes target ID, some ID, and pointer to scale struct)
    FUN_0060add0(g_currentRenderTarget, uVar2, &g_scaleX);
}