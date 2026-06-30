// FUNC_NAME: ColorManager::SetColorAndDispatch
// Address: 0x005311d0
// Role: Stores a 4-component vector (e.g., RGBA color) into a global scratch buffer and, if the current UI context is set to a specific state, dispatches the color to the currently active paint target.

#include <cstdint>

// Global scratch buffer for current color (4 components)
static uint32_t g_currentColor[4] = {0};

// Pointer to current UI context (compared to a static reference)
static void* g_pUIContext = nullptr;          // DAT_012058e8

// Static reference for UI state identification
static void g_uiStateReference;               // placed at &DAT_01219940

// Current paint target pointer (DAT_01219954)
static uint32_t* g_pCurrentPaintTarget = nullptr;

// Static buffers for three possible paint targets
static uint32_t g_paintTargetA;               // DAT_012198f0
static uint32_t g_paintParamA;                // DAT_01219920

static uint32_t g_paintTargetB;               // DAT_01219a48
static uint32_t g_paintParamB;                // DAT_01219a3c

static uint32_t g_paintTargetC;               // DAT_012198f8
static uint32_t g_paintParamC;                // DAT_0121991c

// Forward declaration of the apply function
// Takes destination buffer, an additional parameter, and source color array.
void ApplyColor(uint32_t* dest, uint32_t* param, const uint32_t* src); // FUN_0060add0

void __fastcall SetColorAndDispatch(const uint32_t* colorArray)
{
    // Store the input 4-component vector into global scratch buffer.
    g_currentColor[0] = colorArray[0];
    g_currentColor[1] = colorArray[1];
    g_currentColor[2] = colorArray[2];
    g_currentColor[3] = colorArray[3];

    // Check if the UI context is the one used for color picking/target selection.
    if (g_pUIContext == &g_uiStateReference)
    {
        // Determine which of the three paint targets is currently active.
        if (g_pCurrentPaintTarget == &g_paintTargetA)
        {
            ApplyColor(&g_paintTargetA, &g_paintParamA, colorArray);
            return;
        }
        if (g_pCurrentPaintTarget == &g_paintTargetB)
        {
            ApplyColor(&g_paintTargetB, &g_paintParamB, colorArray);
            return;
        }
        if (g_pCurrentPaintTarget == &g_paintTargetC)
        {
            ApplyColor(&g_paintTargetC, &g_paintParamC, colorArray);
        }
    }
    // Otherwise, do nothing with the stored color.
}