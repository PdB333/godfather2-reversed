// 0x0040e940
// Syncs the engine's mode-routing message bindings to the requested game mode.
//
// Observed mode values from the surrounding string table:
//   1 = paused
//   2 = running
//   3 = frozen
//
// The function unregisters the old mode's root binding, swaps in the
// pre/tick/post message bindings for the new mode, and clears the cached
// dispatch state so the next engine tick starts cleanly.

#include <cstdint>

struct EngineMessageBinding
{
    std::uint32_t messageId;
    std::uint32_t next;
    std::uint32_t flags;
};

extern "C" std::uint32_t FUN_00408a00(std::uint32_t* binding, std::uint8_t force);

extern "C"
{
    // Current and requested engine mode flags.
    extern std::uint32_t g_CurrentGameMode;    // DAT_01205254
    extern std::uint32_t g_RequestedGameMode;  // DAT_01205258

    // Mode-change message bindings.
    extern EngineMessageBinding g_SetRunningModeMessage;  // DAT_012069e4
    extern EngineMessageBinding g_SetPausedModeMessage;    // DAT_012069dc
    extern EngineMessageBinding g_SetFrozenModeMessage;    // DAT_012069cc

    // Tick message bindings for the running mode.
    extern EngineMessageBinding g_RunningPreTickMessage;   // DAT_012069f4
    extern EngineMessageBinding g_RunningTickMessage;      // DAT_012069c4
    extern EngineMessageBinding g_RunningPostTickMessage;  // DAT_012069d4

    // Tick message bindings for the paused mode.
    extern EngineMessageBinding g_PausedPreTickMessage;     // DAT_012069bc
    extern EngineMessageBinding g_PausedTickMessage;        // DAT_012069b4
    extern EngineMessageBinding g_PausedPostTickMessage;    // DAT_012069ec

    // Active bindings published to the rest of the engine.
    extern EngineMessageBinding g_ActivePreTickMessage;     // DAT_012069a8
    extern EngineMessageBinding g_ActiveTickMessage;        // DAT_01206990
    extern EngineMessageBinding g_ActivePostTickMessage;    // DAT_0120699c

    // Per-mode cached state cleared whenever the active mode changes.
    extern std::uint32_t g_ActiveModeResetFlags;            // DAT_012069ac
    extern std::uint32_t g_ActiveModeTickFlags;             // DAT_012069b0
    extern std::uint32_t g_ActiveModePostFlags;             // DAT_01206994
    extern std::uint32_t g_ActiveModeFrameFlags;            // DAT_01206998
    extern std::uint32_t g_ActiveModeStateA;                // DAT_012069a0
    extern std::uint32_t g_ActiveModeStateB;                // DAT_012069a4
}

static void UnregisterModeBinding(const EngineMessageBinding& sourceBinding)
{
    // FUN_00408a00 mutates a binding node in-place, so operate on a local copy.
    EngineMessageBinding binding = sourceBinding;
    binding.next = 0;
    binding.flags = 0;
    FUN_00408a00(reinterpret_cast<std::uint32_t*>(&binding), 0);
}

void SyncGameModeMessageBindings()
{
    if (g_CurrentGameMode == g_RequestedGameMode)
    {
        return;
    }

    g_CurrentGameMode = g_RequestedGameMode;

    if (g_RequestedGameMode == 1)
    {
        // Paused mode.
        UnregisterModeBinding(g_SetPausedModeMessage);
        g_ActivePreTickMessage = g_PausedPreTickMessage;
        g_ActiveTickMessage = g_PausedTickMessage;
        g_ActivePostTickMessage = g_PausedPostTickMessage;
    }
    else if (g_RequestedGameMode == 2)
    {
        // Running mode.
        UnregisterModeBinding(g_SetRunningModeMessage);
        g_ActivePreTickMessage = g_RunningPreTickMessage;
        g_ActiveTickMessage = g_RunningTickMessage;
        g_ActivePostTickMessage = g_RunningPostTickMessage;
    }
    else if (g_RequestedGameMode == 3)
    {
        // Frozen mode disables the active tick routing entirely.
        UnregisterModeBinding(g_SetFrozenModeMessage);

        g_ActivePreTickMessage.messageId = 0;
        g_ActivePreTickMessage.next = 0;
        g_ActivePreTickMessage.flags = 0;

        g_ActiveTickMessage.messageId = 0;
        g_ActiveTickMessage.next = 0;
        g_ActiveTickMessage.flags = 0;

        g_ActivePostTickMessage.messageId = 0;
        g_ActivePostTickMessage.next = 0;
        g_ActivePostTickMessage.flags = 0;
    }
    else
    {
        return;
    }

    // Mode transitions reset the cached dispatcher state so the next tick
    // rebuilds its message routing from scratch.
    g_ActiveModeResetFlags = 0;
    g_ActiveModeTickFlags = 0;
    g_ActiveModePostFlags = 0;
    g_ActiveModeFrameFlags = 0;
    g_ActiveModeStateA = 0;
    g_ActiveModeStateB = 0;
}
