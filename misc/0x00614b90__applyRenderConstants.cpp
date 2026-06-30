// FUNC_NAME: applyRenderConstants

#include <cstring>

// Global constants (default and working copies)
static ShaderConstants g_defaultConstantsA; // 0x011f6a30
static ShaderConstants g_defaultConstantsB; // 0x011f6af0
static ShaderConstants g_workingConstantsA;  // 0x011f67b0
static ShaderConstants g_workingConstantsB;  // 0x011f6830
static PostProcessData g_postProcessData;    // 0x011f6b70

// Renderer pointer (0x012058e8)
static Renderer* g_pRenderer = nullptr;

void applyRenderConstants(void) {
    // Reset state (likely clear dirty flags or reset default values)
    resetDefaultState();
    resetDefaultState();

    // Copy first set of default constants to working buffer (16 DWORDs = 64 bytes)
    std::memcpy(&g_workingConstantsA, &g_defaultConstantsA, sizeof(g_workingConstantsA));

    // If renderer is valid and first constant buffer upload handle is non‑null
    if (g_pRenderer != nullptr && g_pRenderer->constantBufferSize[0] != 0) {
        // Upload constants to GPU: renderer handle, size, and buffer pointer
        uploadConstantsToDevice(
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(g_pRenderer) + 0x10), // device/context handle
            g_pRenderer->constantBufferSize[0], // size of buffer (offset 0x3C)
            &g_workingConstantsA
        );
    }

    // Copy second set of default constants
    std::memcpy(&g_workingConstantsB, &g_defaultConstantsB, sizeof(g_workingConstantsB));

    // Similar upload for second constant buffer (offset 0x48)
    if (g_pRenderer != nullptr && g_pRenderer->constantBufferSize[1] != 0) {
        uploadConstantsToDevice(
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(g_pRenderer) + 0x10),
            g_pRenderer->constantBufferSize[1],
            &g_workingConstantsB
        );
    }

    // Finalize with post‑processing data
    processPostData(&g_postProcessData);
}