// Reconstructed from Ghidra decompile at 0x0040DD80.
// Per-frame update dispatcher for the active engine/gameplay state.

#include <cstdint>

struct EngineViewState
{
    // The decompile reads a 32-bit mode/flag at offset 0x39F8 from the
    // sub-object pointed to by g_engineHost->viewState.
    std::uint8_t reserved[0x39F8];
    std::uint32_t frameModeFlag;
};

struct EngineHost
{
    std::uint32_t reserved0;
    EngineViewState* viewState;
};

extern "C" {
    // Global frame counter incremented once per call.
    extern std::uint32_t g_frameTickCount;      // DAT_0120523c

    // Root engine/game state pointer used for frame-gating checks.
    extern EngineHost* g_engineHost;            // DAT_012233a8

    // Non-zero when the fallback frame update path is enabled.
    extern std::uint8_t g_frameUpdateEnabled;   // DAT_01205358

    // Active session/object pointer. When null, the renderer is reset to a
    // default state before the frame is finalized.
    extern void* g_activeSession;               // DAT_012233ac

    void FUN_0041f2a0(void);
    void FUN_00414040(void);
    void FUN_0044ec10(void);
    void FUN_00609730(float r, float g, float b, float a,
                      std::uint32_t color, std::uint32_t flags);
    void FUN_00609810(std::uint32_t state);
}

extern "C" void FUN_0040dd80(void)
{
    g_frameTickCount++;

    // If the engine has no host state, or the current host is in the special
    // mode that forces a fallback update, or frame updates are globally gated
    // off, run the secondary update path before continuing.
    if ((g_engineHost == nullptr) ||
        (g_engineHost->viewState->frameModeFlag == 1) ||
        (g_frameUpdateEnabled == '\0')) {
        FUN_0041f2a0();
    }

    // Main per-frame engine logic.
    FUN_00414040();

    // Secondary frame work, likely rendering/buffer maintenance.
    FUN_0044ec10();

    // When no active gameplay/session object is bound, restore a default
    // render state and submit the fallback render selector.
    if (g_activeSession == nullptr) {
        FUN_00609730(0.0f, 0.0f, 0.0f, 0.0f, 0x3f800000u, 0u);
        FUN_00609810(0x0Fu);
    }
}
