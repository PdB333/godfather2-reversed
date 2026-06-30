// FUNC_NAME: PresentationManager::applyWidescreenCorrection

// Reconstructed C++ code for function at 0x005262b0
// Handles widescreen scaling and viewport reset when resolution changes.

// Global constants and state (simulated from observed memory addresses)
// These are likely static members of PresentationManager
static float g_defaultScreenWidth = DAT_00e2b1a4;  // e.g., 1280.0f - reference width
static float g_viewportLeft   = _DAT_01125200;     // current left clip
static float g_viewportRight  = _DAT_01125204;     // current right clip
static float g_viewportTop    = _DAT_01125208;     // current top clip
static float g_viewportBottom = _DAT_0112520c;     // current bottom clip
static float g_viewportWidth  = DAT_01125220;      // current viewport width
static float g_viewportHeight = _DAT_011251f4;     // current viewport height (stored as _DAT_011251f4)
static float g_viewportXOffset = DAT_011251f8;      // offset/delta X
static uint32 g_viewportFlags = _DAT_011251f0;      // flags (bit 28 used for conditional)
static float g_reserved1 = _DAT_01125210;           // unknown
static float g_reserved2 = _DAT_01125214;           // unknown
static float g_reserved3 = _DAT_01125218;           // unknown
static float g_reserved4 = _DAT_0112521c;           // unknown, set to default width later

// Forward declaration for the called function (likely sets up projection/matrix)
void PresentationManager::setViewport(float x, float y, int unk); // FUN_005263c0

void PresentationManager::applyWidescreenCorrection(void)
{
    float scaleFactor;

    // Only apply if viewport dimensions are valid and non-zero
    // g_viewportWidth is the current virtual width, g_viewportHeight and X offset must be positive/non-zero
    if ((g_viewportWidth != 0.0f) && (0.0f < g_viewportHeight) && (g_viewportXOffset != 0.0f))
    {
        // Compute scaling factor relative to default width
        scaleFactor = g_defaultScreenWidth / g_viewportWidth;

        // Scale viewport bounds proportionally
        g_viewportLeft   = scaleFactor * g_viewportLeft;
        g_viewportRight  = scaleFactor * g_viewportRight;
        g_viewportTop    = scaleFactor * g_viewportTop;
        g_viewportBottom = scaleFactor * g_viewportBottom;

        // If the viewport update flag (bit 28) is not set, update the projection/viewport
        if ((g_viewportFlags & 0x10000000) == 0)
        {
            // Call with current height and X offset; third parameter is 0 (reset)
            PresentationManager::setViewport(g_viewportHeight, g_viewportXOffset, 0);
        }

        // Reset viewport state to defaults for next frame
        g_viewportHeight = 0.0f;
        g_viewportXOffset = 0.0f;
        g_viewportFlags = 0;
        g_viewportBottom = 0.0f;
        g_reserved1 = 0;
        g_reserved2 = 0;
        g_reserved3 = 0;
        g_viewportWidth = 0.0f;

        // Restore viewport bounds to full default width (no scaling)
        g_viewportLeft   = g_defaultScreenWidth;
        g_viewportRight  = g_defaultScreenWidth;
        g_viewportTop    = g_defaultScreenWidth;
        g_reserved4      = g_defaultScreenWidth; // bottom? stored as _DAT_0112521c
    }
    return;
}