// 0x0040ec50
// Registers the engine message IDs used by the game-mode dispatcher.
//
// This initializer interns the message names for the mode switch events and the
// per-mode tick callbacks, then stores the resulting ids into the corresponding
// global binding slots. Later code compares against these cached ids when
// switching between running, paused, and frozen dispatch paths.

#include <cstdint>

struct EngineMessageBinding
{
    std::uint32_t messageId;
    std::uint32_t next;
    std::uint32_t flags;
};

extern "C"
{
    std::uint32_t FUN_004dafd0(const char* messageName);
    void FUN_00408260(std::uint32_t* bindingSlot, std::uint32_t messageId);

    extern EngineMessageBinding g_SetRunningModeMessage;   // DAT_012069e4
    extern EngineMessageBinding g_SetPausedModeMessage;    // DAT_012069dc
    extern EngineMessageBinding g_SetFrozenModeMessage;    // DAT_012069cc

    extern EngineMessageBinding g_RunningPreTickMessage;   // DAT_012069f4
    extern EngineMessageBinding g_RunningTickMessage;      // DAT_012069c4
    extern EngineMessageBinding g_RunningPostTickMessage;  // DAT_012069d4

    extern EngineMessageBinding g_PausedPreTickMessage;    // DAT_012069bc
    extern EngineMessageBinding g_PausedTickMessage;       // DAT_012069b4
    extern EngineMessageBinding g_PausedPostTickMessage;   // DAT_012069ec
}

static void RegisterMessageBinding(EngineMessageBinding& binding, const char* messageName)
{
    const std::uint32_t messageId = FUN_004dafd0(messageName);

    // FUN_00408260 writes the interned id into the engine's binding node.
    FUN_00408260(reinterpret_cast<std::uint32_t*>(&binding), messageId);
}

extern "C" void InitializeGameModeMessageBindings()
{
    // Mode transition messages.
    RegisterMessageBinding(g_SetRunningModeMessage, "iMsgSetRunningMode");
    RegisterMessageBinding(g_SetPausedModeMessage, "iMsgSetPausedMode");
    RegisterMessageBinding(g_SetFrozenModeMessage, "iMsgSetFrozenMode");

    // Running-state tick pipeline.
    RegisterMessageBinding(g_RunningPreTickMessage, "iMsgRunningPreTick");
    RegisterMessageBinding(g_RunningTickMessage, "iMsgRunningTick");
    RegisterMessageBinding(g_RunningPostTickMessage, "iMsgRunningPostTick");

    // Paused-state tick pipeline.
    RegisterMessageBinding(g_PausedPreTickMessage, "iMsgPausedPreTick");
    RegisterMessageBinding(g_PausedTickMessage, "iMsgPausedTick");
    RegisterMessageBinding(g_PausedPostTickMessage, "iMsgPausedPostTick");
}
