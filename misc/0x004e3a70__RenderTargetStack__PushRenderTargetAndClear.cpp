// FUNC_NAME: RenderTargetStack::PushRenderTargetAndClear
// Address: 0x004e3a70
// Role: Pushes a new render target onto the stack, clearing it, and manages depth-stencil state.

// Global render target stack (20 entries max)
struct RenderTargetEntry {
    int surfaceId;       // +0x00
    int flags;           // +0x04
};

// Global state
static int sCurrentRenderTargetId;        // DAT_011f3910
static int sCurrentRenderTargetFlags;     // DAT_011f3914
static int sDefaultRenderTargetId;        // DAT_012058a8
static int sDefaultDepthStencilId;        // DAT_012058a4

// Render device pointer; if non-null, provides custom backbuffer/depth surfaces at +0x170 and +0x16c
static void* g_RenderDevice;              // DAT_012054dc

// Stack of pushed render targets (used for restoring later?)
static RenderTargetEntry g_RenderTargetStack[20]; // DAT_01218e50 (surfaceId) and DAT_01218e54 (flags) interleaved

// Another stack for depth-stencil state (used for pushing?)
static int sPushedDepthStencilId;         // DAT_011f38f0
static int sPushedDepthStencilFlags;      // DAT_011f38f4

// Helper: pushes a render state onto a save stack
void FUN_00609340(int mode, int oldVal1, int oldVal2, int context);
// Helper: applies pending state changes
void FUN_0060dc10();
// Helper: sets clear color/depth
void FUN_0060db60(float r, float g, float b, float a, float depth);

void __thiscall pushRenderTargetAndClear(int newSurfaceId)
{
    int oldSurfaceId = sCurrentRenderTargetId;
    int oldFlags = sCurrentRenderTargetFlags;

    // Switch to default surface
    sCurrentRenderTargetId = sDefaultRenderTargetId;
    sCurrentRenderTargetFlags = 0;

    // Push old state onto save stack
    FUN_00609340(4, oldSurfaceId, oldFlags, newSurfaceId);

    // Apply state immediately? (flush)
    FUN_0060dc10();

    // Determine the actual depth-stencil surface to use
    int depthStencilId = sDefaultDepthStencilId;
    if (g_RenderDevice != nullptr) {
        depthStencilId = *(int*)((char*)g_RenderDevice + 0x16c); // +0x16c: depthStencilSurface
    }

    // Search the render target stack for an entry matching this depth-stencil ID
    for (int i = 0; i < 20; i++) {
        if (g_RenderTargetStack[i].surfaceId == depthStencilId) {
            // Clear bits 0 and 1 in the flags (likely to mark as not "locked" or "active")
            g_RenderTargetStack[i].flags &= ~3;
            break;
        }
    }

    // Determine the actual backbuffer surface
    int backbufferId = depthStencilId; // initially same
    if (g_RenderDevice != nullptr) {
        backbufferId = *(int*)((char*)g_RenderDevice + 0x170); // +0x170: backbufferSurface
    }

    // Push the depth-stencil state onto a separate stack
    int oldPushedDepthStencilId = sPushedDepthStencilId;
    int oldPushedDepthStencilFlags = sPushedDepthStencilFlags;
    sPushedDepthStencilId = depthStencilId;
    sPushedDepthStencilFlags = 0;

    FUN_00609340(0, oldPushedDepthStencilId, oldPushedDepthStencilFlags, newSurfaceId);

    // Set clear color to black, alpha=1, depth=1 (standard clear state)
    FUN_0060db60(0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
}