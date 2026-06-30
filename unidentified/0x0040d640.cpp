// 0x0040d640
// Render bootstrap for The Godfather II (EA / EARS engine).
//
// This function resolves the engine message IDs used by the render pipeline,
// resets the shared render tint/state block, and then kicks a handful of
// downstream render/material subsystems online.

#include <cstdint>

extern "C" {
    std::uint32_t FUN_004dafd0(const char* messageName);
    void FUN_00408260(std::uint32_t* slot, std::uint32_t messageId);
    void FUN_0061b300();
    void FUN_00618fc0();
    void FUN_00610d70(int enableFullScreenRender);
    void FUN_0061a3c0();
    void FUN_0049d2e0();

    // Cached engine message IDs for render-phase notifications.
    extern std::uint32_t DAT_01206960; // iMsgBeforeRender
    extern std::uint32_t DAT_01206980; // iMsgPreRender
    extern std::uint32_t DAT_01206970; // iMsgDoRender
    extern std::uint32_t DAT_01206978; // iMsgDoRenderFullScreen
    extern std::uint32_t DAT_01206988; // iMsgDoRenderFullScreenDebug
    extern std::uint32_t DAT_01206968; // iMsgPreShowRaster

    // Shared render tint / state used by later rendering code.
    extern float DAT_00e2cd54;
    extern float DAT_00e2b1a4;
    extern float g_RenderColorR; // DAT_011f4220
    extern float g_RenderColorG; // DAT_011f4224
    extern float g_RenderColorB; // DAT_011f4228
    extern float g_RenderColorA; // DAT_011f422c
    extern std::uint32_t g_RenderColorMode; // DAT_011f4230
    extern std::uint32_t g_RenderColorEnabled; // DAT_011f4234
}

extern "C" void InitializeRenderPhaseMessagesAndState()
{
    // Populate the message table with the render-phase notifications used by
    // the engine's draw dispatch path.
    std::uint32_t messageId = FUN_004dafd0("iMsgBeforeRender");
    FUN_00408260(&DAT_01206960, messageId);

    messageId = FUN_004dafd0("iMsgPreRender");
    FUN_00408260(&DAT_01206980, messageId);

    messageId = FUN_004dafd0("iMsgDoRender");
    FUN_00408260(&DAT_01206970, messageId);

    messageId = FUN_004dafd0("iMsgDoRenderFullScreen");
    FUN_00408260(&DAT_01206978, messageId);

    messageId = FUN_004dafd0("iMsgDoRenderFullScreenDebug");
    FUN_00408260(&DAT_01206988, messageId);

    messageId = FUN_004dafd0("iMsgPreShowRaster");
    FUN_00408260(&DAT_01206968, messageId);

    // Reset the shared render color/state block to its default startup values.
    // Later material and UI code reads this as a four-channel color vector.
    g_RenderColorR = DAT_00e2cd54;
    g_RenderColorG = DAT_00e2cd54;
    g_RenderColorB = DAT_00e2cd54;
    g_RenderColorEnabled = 0;
    g_RenderColorA = DAT_00e2b1a4;
    g_RenderColorMode = 0;

    // Bring the downstream render/material subsystems online.
    FUN_0061b300();
    FUN_00618fc0();
    FUN_00610d70(1);
    FUN_0061a3c0();
    FUN_0049d2e0();
}
