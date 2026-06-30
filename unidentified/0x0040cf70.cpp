// Reconstructed function: InitializeSystemMessageIds
// Address: 0x0040cf70
//
// This startup helper interns three engine message names and stores the resulting
// message identifiers into global slots used by the core system message pipeline.
// The exact intern/lookup routine is opaque in the exports, but its usage pattern
// is consistent across the project: convert a string name into a stable numeric
// message id, then register that id in the message table.

#include <cstdint>

extern "C" {
    // Likely returns a stable engine message id for the provided string token.
    std::uint32_t FUN_004dafd0(const char* name);

    // Registers the message id in the engine's message table / reference tracker.
    void FUN_00408260(std::uint32_t* messageSlot, std::uint32_t messageId);

    // Global storage for the core system message ids.
    extern std::uint32_t DAT_01206950; // iMsgStartSystem
    extern std::uint32_t DAT_01206948; // iMsgStopSystem
    extern std::uint32_t DAT_01206940; // iMsgSystemTick
}

extern "C" void InitializeSystemMessageIds()
{
    // These message names are used by the engine's lifecycle dispatcher.
    // The ids are cached globally so later code can compare and route messages
    // without re-interning the strings every time.
    std::uint32_t startSystemId = FUN_004dafd0("iMsgStartSystem");
    FUN_00408260(&DAT_01206950, startSystemId);

    std::uint32_t stopSystemId = FUN_004dafd0("iMsgStopSystem");
    FUN_00408260(&DAT_01206948, stopSystemId);

    std::uint32_t systemTickId = FUN_004dafd0("iMsgSystemTick");
    FUN_00408260(&DAT_01206940, systemTickId);
}
