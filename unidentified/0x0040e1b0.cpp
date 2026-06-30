// Reconstructed function at 0x0040e1b0
// Emits a begin/end pair of stream markers around an optional simulation update.
//
// Ghidra shows this routine writing one 4-byte token into the global command
// stream, invoking FUN_00486d30() if the global simulation context exists, and
// then writing a matching closing token. The pattern matches the engine's
// event / command marshalling path.

#include <cstdint>

struct EngineCommandStream
{
    std::uint8_t reserved[0x14];
    std::uint32_t* write_cursor; // Offset 0x14 in the original structure.
};

extern "C" {
    // Global stream / command writer used by the engine.
    extern EngineCommandStream* DAT_01206880;

    // Optional global context that gets advanced between the two markers.
    extern void* DAT_01223380;

    // Marker tokens emitted into the stream.
    extern std::uint8_t PTR_LAB_0110b0a4;
    extern std::uint8_t PTR_LAB_0110b0b8;

    // Advances the simulation / timed-work context.
    void FUN_00486d30(void* context);
}

static inline void WriteStreamToken(EngineCommandStream* stream, const std::uint8_t* token)
{
    // The stream stores raw 32-bit entries; each token is written as a pointer value.
    *stream->write_cursor = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(token));
    stream->write_cursor += 1;
}

extern "C" void EmitSimulationUpdateMarkers(void)
{
    // Emit the opening marker for the engine stream block.
    WriteStreamToken(DAT_01206880, &PTR_LAB_0110b0a4);

    // If the global simulation state exists, let it advance between the two markers.
    if (DAT_01223380 != nullptr) {
        FUN_00486d30(DAT_01223380);
    }

    // Emit the closing marker to finish the stream block.
    WriteStreamToken(DAT_01206880, &PTR_LAB_0110b0b8);
}
