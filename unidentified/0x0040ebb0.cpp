// 0x0040ebb0
// Per-frame pump for the active game-mode message bindings.
//
// The function keeps the requested game mode in sync with the active routing
// table, then drives the engine's pre-tick / tick / post-tick message chains
// when timing is enabled. The current frame serial is captured before the
// increment so downstream code can associate the post-tick work with the same
// frame generation.

#include <cstdint>

struct EngineMessageBinding
{
    std::uint32_t messageId;
    std::uint32_t next;
    std::uint32_t flags;
};

struct EngineCommandStream
{
    std::uint8_t reserved[0x14];
    std::uint32_t* writeCursor; // Offset 0x14 in the original structure.
};

extern "C"
{
    // Game-mode state managed by the nearby sync helper at 0x0040e940.
    extern std::uint32_t g_CurrentGameMode;   // DAT_01205254
    extern std::uint32_t g_RequestedGameMode; // DAT_01205258

    // Timing gate. When zero, the per-frame message pump is skipped.
    extern std::uint8_t g_TimingEnabled;      // DAT_0110accb

    // Monotonic frame serial used by the main loop.
    extern std::uint32_t g_FrameDispatchCounter; // DAT_01205250

    // Engine command stream used to emit frame markers.
    extern EngineCommandStream* g_EngineCommandStream; // DAT_01206880

    // Active bindings selected by SyncGameModeMessageBindings().
    extern EngineMessageBinding g_ActivePreTickBinding;  // DAT_012069a8
    extern EngineMessageBinding g_ActiveTickBinding;     // DAT_01206990
    extern EngineMessageBinding g_ActivePostTickBinding; // DAT_0120699c

    // Frame stamp published for the current post-tick work.
    extern std::uint32_t g_FrameDispatchStamp; // DAT_01206994

    // Message id for the delete-entity notification.
    extern std::uint32_t g_DeleteEntityMessageId; // DAT_012067c4

    void SyncGameModeMessageBindings();
    std::uint32_t FUN_00408a00(std::uint32_t* binding, std::uint8_t force);
    void FUN_0041e8d0(void);
    void FUN_00408800(std::uint32_t messageId, std::uint32_t param2, std::uint32_t param3);

    extern std::uint8_t PTR_LAB_0110b0cc;
}

static inline void PushStreamToken(EngineCommandStream* stream, const void* token)
{
    *stream->writeCursor = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(token));
    stream->writeCursor += 1;
}

void PumpFrameMessageBindings()
{
    // Keep the active bindings aligned with the mode requested by the rest of
    // the engine before processing the frame.
    if (g_CurrentGameMode != g_RequestedGameMode)
    {
        SyncGameModeMessageBindings();
    }

    // When timing is disabled, the engine does not advance the per-frame
    // message chain.
    if (g_TimingEnabled == 0)
    {
        return;
    }

    // Pre-tick subscribers run before the command-stream marker is emitted.
    FUN_00408a00(reinterpret_cast<std::uint32_t*>(&g_ActivePreTickBinding), 0);

    // Capture the current frame serial for the post-tick phase, then advance
    // the global counter for the next loop iteration.
    g_FrameDispatchStamp = g_FrameDispatchCounter;
    g_FrameDispatchCounter += 1;

    // The original code writes a frame marker into the command stream here.
    PushStreamToken(g_EngineCommandStream, &PTR_LAB_0110b0cc);

    // Tick and post-tick dispatch use the bindings selected by the current
    // game mode.
    FUN_00408a00(reinterpret_cast<std::uint32_t*>(&g_ActiveTickBinding), 0);
    FUN_0041e8d0();
    FUN_00408a00(reinterpret_cast<std::uint32_t*>(&g_ActivePostTickBinding), 0);

    // Flush the delete-entity notification if the message id has been
    // registered.
    if (g_DeleteEntityMessageId != 0)
    {
        FUN_00408800(g_DeleteEntityMessageId, 0, 0);
    }
}
