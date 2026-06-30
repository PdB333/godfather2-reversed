// FUNC_NAME: RenderDevice::setupViewport
// Address: 0x00609500
// This function sets up viewport parameters for the render device, including left/right/top/bottom (pixel coords) and near/far clip planes.
// It computes scaling factors for the viewport dimensions and applies them to two contexts (possibly stereo or split-screen).
// The render device is a global singleton at DAT_01205750.

class RenderDevice;

extern RenderDevice* g_pRenderDevice; // DAT_01205750

// Global viewport data structures (stored at fixed addresses)
extern struct ViewportData {
    int left;        // +0x00 (param_1)
    int right;       // +0x04 (in_EAX)
    int top;         // +0x08 (unaff_EDI)
    int bottom;      // +0x0C (param_2)
    float nearClip;  // +0x10 (in_XMM0_Da)
    float farClip;   // +0x14 (param_3)
    int someSum1;   // +0x18 (param_1 + unaff_EDI) // left + top?
    int someSum2;   // +0x1C (in_EAX + param_2)   // right + bottom?
} g_ViewportData; // at 0x011d91c0

extern struct ViewportScale {
    float scaleX;   // +0x00 (DAT_00e2b1a4 / (float)unaff_EDI)
    float scaleY;   // +0x04 (DAT_00e2b1a4 / (float)param_2)
    float scaleX2;  // +0x08 (scaleX * DAT_00e2cd54)
    float scaleY2;  // +0x0C (scaleY * DAT_00e2cd54)
} g_ViewportScale; // at 0x011f6680

// Global constants used for scaling
extern float g_ScreenHeight;      // DAT_00e2b1a4
extern float g_SomeFactor;        // DAT_00e2cd54

// External functions
void applyViewportScaling(void* context1, void* context2, float* scaleParams); // FUN_0060add0

// Global state for two rendering contexts (e.g., left/right eye or split-screen)
extern void* g_RenderContext;    // DAT_012058e8  (pointer to something with sub-structures)

extern int g_MinViewportSize;    // DAT_012058d4 (clamped to at least 174)
extern int g_MaxViewportSize;    // DAT_00f1598c (clamped to at most 174)

extern int g_ViewportFlag;       // _DAT_011f3c90 (set to 0)

void __thiscall RenderDevice::setupViewport(int left, int top, int right, int bottom, float nearClip, float farClip)
{
    // Store viewport rectangle and clip planes into global structure
    g_ViewportData.left = left;
    g_ViewportData.right = right;
    g_ViewportData.top = bottom; // Note: param_2 is top/bottom? Actually param_2 is stored as bottom
    g_ViewportData.bottom = top; // Wait: the decompile shows: _DAT_011d91c0 = param_1 (left), _DAT_011d91c4 = in_EAX (right), _DAT_011d91c8 = unaff_EDI (top?), _DAT_011d91cc = param_2 (bottom?). But then _DAT_011d91e0 = param_1 + unaff_EDI, _DAT_011d91e4 = in_EAX + param_2. So unaff_EDI is used with left, param_2 with right. So likely top is unaff_EDI, bottom is param_2. However, the order is confusing. For clarity, we'll keep the parameter order as given: param_1 (left), param_2 (? ), in_EAX (right), unaff_EDI (top), param_3 (farClip), in_XMM0_Da (nearClip). But to avoid confusion, we'll map to appropriate names.

    // The function actually receives 6 parameters: left, top, right, bottom, near, far. But the decompiler shows 3 stack params plus 3 register vars. Based on usage:
    // left = param_1, top = unaff_EDI, right = in_EAX, bottom = param_2, near = in_XMM0_Da, far = param_3.
    // We'll use that mapping:
    int left = param_1;
    int top = unaff_EDI;
    int right = in_EAX;
    int bottom = param_2;
    float nearClip = in_XMM0_Da;
    float farClip = param_3;

    g_ViewportData.left = left;
    g_ViewportData.right = right;
    g_ViewportData.top = bottom; // Actually bottom stored at +0x0C? No, the decompile stores param_2 at 0x011d91cc, which we call bottom.
    g_ViewportData.bottom = top; // Wait, need to re-examine: The decompile writes:
    // _DAT_011d91c0 = param_1; (left)
    // _DAT_011d91c4 = in_EAX; (right)
    // _DAT_011d91c8 = unaff_EDI; (top)
    // _DAT_011d91cc = param_2; (bottom)
    // _DAT_011d91d0 = in_XMM0_Da; (near)
    // _DAT_011d91d4 = param_3; (far)
    // _DAT_011d91d8 = param_1; (left again)
    // _DAT_011d91dc = in_EAX; (right again)
    // _DAT_011d91e0 = param_1 + unaff_EDI; (left+top)
    // _DAT_011d91e4 = in_EAX + param_2; (right+bottom)
    // So the structure has:
    // +0x00: left
    // +0x04: right
    // +0x08: top
    // +0x0C: bottom
    // +0x10: near
    // +0x14: far
    // +0x18: left+top (some sum)
    // +0x1C: right+bottom (some sum)
    // Then the second part starting at +0x18 is used for another call.

    g_ViewportData.left = left;
    g_ViewportData.right = right;
    g_ViewportData.top = top;
    g_ViewportData.bottom = bottom;
    g_ViewportData.nearClip = nearClip;
    g_ViewportData.farClip = farClip;
    g_ViewportData.someSum1 = left + top;
    g_ViewportData.someSum2 = right + bottom;

    // Notify render device of viewport data (vtable offset 0xbc)
    g_pRenderDevice->setViewportData(&g_ViewportData);

    // Compute scaling factors for viewport
    g_ViewportScale.scaleX = g_ScreenHeight / (float)top;   // _DAT_011f6680 = DAT_00e2b1a4 / (float)unaff_EDI
    g_ViewportScale.scaleY = g_ScreenHeight / (float)bottom; // fRam011f6684 = DAT_00e2b1a4 / (float)param_2
    g_ViewportScale.scaleX2 = g_ViewportScale.scaleX * g_SomeFactor; // fRam011f6688
    g_ViewportScale.scaleY2 = g_ViewportScale.scaleY * g_SomeFactor; // fRam011f668c

    // Copy scaling factors to local stack to pass to context setup
    float localScale[4] = { g_ViewportScale.scaleX, g_ViewportScale.scaleY, g_ViewportScale.scaleX2, g_ViewportScale.scaleY2 };

    // Apply scale to render contexts if they exist
    if (g_RenderContext != nullptr) {
        if (*(int*)(g_RenderContext + 0x60) != 0) {
            applyViewportScaling(*(void**)(g_RenderContext + 0x14), *(void**)(g_RenderContext + 0x60), localScale);
        }
        if (*(int*)(g_RenderContext + 100) != 0) { // 0x64
            applyViewportScaling(*(void**)(g_RenderContext + 0x10), *(void**)(g_RenderContext + 100), localScale);
        }
    }

    // Apply viewport data to render device (vtable offset 300 = 0x12c)
    g_pRenderDevice->applyViewport(&g_ViewportData.someSum1); // passes ptr to left+top

    // Enforce minimum viewport size (174)
    if (g_MinViewportSize < 0xae) {
        g_MinViewportSize = 0xae; // 174
    }
    g_ViewportFlag = 0;

    // Enforce maximum viewport size (174)
    if (g_MaxViewportSize > 0xae) {
        g_MaxViewportSize = 0xae; // 174
    }
}