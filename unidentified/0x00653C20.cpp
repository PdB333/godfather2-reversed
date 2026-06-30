// 0x00653C20 - TNLConnection::PumpOutgoingTraffic(std::uint32_t nowMs)
//
// Per-tick transport service for the game-specific TNL connection object.
// This routine has two distinct pacing regimes:
// - unthrottled mode: accumulate local time and suppress repeated pumps until
//   the configured minimum interval has elapsed;
// - throttled mode: use reliable-sequence progress plus elapsed time to decide
//   when the next outbound packet should be committed.
//
// When the connection is clear to send and a packet is waiting, the function
// primes a fresh stream, serializes the payload, and clears the temporary
// packet builder state. The exact vtable slots at +0x34 and +0x54 are not
// named by the export, so they are kept as "preflight" / "has pending work"
// hooks in the reconstruction.

#include <cstdint>

extern float DAT_00e35654;
extern float DAT_00e3ac54;
extern float DAT_00e44578;
extern double _DAT_00e44960;

extern "C" void FUN_006530a0(int mode);
extern "C" void FUN_00653a60(void);
extern "C" void FUN_00653df0(void);
extern "C" void FUN_0064b440(void);

struct TNLConnection
{
    void* vftable;                       // 0x00
    std::uint8_t pad_04[0x8c];           // 0x04..0x8f

    // Reliable sequence head used by the throttled send path.
    std::uint32_t currentReliableSequence;   // 0x90
    std::uint32_t oldestUnackedSequence;     // 0x94
    std::uint32_t nextSendSequence;          // 0x98

    std::uint8_t pad_9c[0x1c];           // 0x9c..0xb7
    std::uint8_t modeFlags;              // 0xb8
    std::uint8_t pad_b9[0x03];           // 0xb9..0xbb

    // Timer used by the non-throttled pump gate.
    std::uint32_t lastPaceCheckMs;       // 0xbc
    std::uint8_t pad_c0[0x04];           // 0xc0..0xc3
    std::uint32_t paceCarryMs;           // 0xc4

    std::uint8_t pad_c8[0x34];           // 0xc8..0xfb
    std::uint32_t minPumpIntervalMs;     // 0xfc

    std::uint8_t pad_100[0xc0];          // 0x100..0x1bf
    std::uint32_t lastCommittedSequence; // 0x1c0
    std::uint32_t lastCommittedTickMs;   // 0x1c4

    std::uint32_t __thiscall ComputeOutboundWindowState() const;
    void __thiscall PumpOutgoingTraffic(std::uint32_t nowMs);
};

static inline void CallVTableSlot34(TNLConnection* self)
{
    using Fn = void(__thiscall*)(TNLConnection*);
    auto* const vtable = *reinterpret_cast<void***>(self);
    reinterpret_cast<Fn>(vtable[0x34 / sizeof(void*)])(self);
}

static inline bool CallVTableSlot54(TNLConnection* self)
{
    using Fn = bool(__thiscall*)(TNLConnection*);
    auto* const vtable = *reinterpret_cast<void***>(self);
    return reinterpret_cast<Fn>(vtable[0x54 / sizeof(void*)])(self);
}

void __thiscall TNLConnection::PumpOutgoingTraffic(std::uint32_t nowMs)
{
    // In the simpler transport modes, the connection runs on a soft
    // millisecond budget. The accumulator advances only when enough time has
    // elapsed to justify another pump.
    if ((modeFlags & 0x0c) == 0) {
        const std::uint32_t elapsedSinceCheckpoint =
            (paceCarryMs - lastPaceCheckMs) + nowMs;

        if (elapsedSinceCheckpoint < minPumpIntervalMs) {
            return;
        }

        paceCarryMs = (paceCarryMs - lastPaceCheckMs) - minPumpIntervalMs + nowMs;
        if (1000u < paceCarryMs) {
            paceCarryMs = 1000u;
        }
    }

    // Slot +0x34 is a per-tick preflight hook on the connection object.
    // The original engine uses it to advance transport-local state before
    // deciding whether a packet should be emitted.
    CallVTableSlot34(this);

    // If the reliable window is clear and the object still has a packet to
    // flush, build a new outbound stream and commit it immediately.
    if ((ComputeOutboundWindowState() == 0u) && CallVTableSlot54(this)) {
        lastPaceCheckMs = nowMs;

        // `FUN_006530a0(0)` starts a fresh packet stream / builder state.
        // `FUN_00653df0()` serializes the queued payload into the active
        // transport path, and `FUN_0064b440()` clears the temporary packet
        // object once the commit has been issued.
        FUN_006530a0(0);
        FUN_00653df0();
        FUN_0064b440();
        return;
    }

    // In throttled transport modes, the sender uses reliable sequence progress
    // as an additional pacing signal. The sequence delta and elapsed time are
    // multiplied by tuning constants from the original binary to avoid spamming
    // the network with repeated updates when the head does not advance.
    if ((modeFlags & 0x0c) != 0) {
        const std::int32_t sequenceDelta =
            static_cast<std::int32_t>(currentReliableSequence) -
            static_cast<std::int32_t>(lastCommittedSequence);

        float elapsedAsFloat = static_cast<float>(
            static_cast<std::int32_t>(nowMs) - static_cast<std::int32_t>(lastCommittedTickMs));
        if (static_cast<std::int32_t>(nowMs) - static_cast<std::int32_t>(lastCommittedTickMs) < 0) {
            elapsedAsFloat += DAT_00e44578;
        }

        if (((1.0f < static_cast<float>(sequenceDelta) * DAT_00e35654 * elapsedAsFloat * DAT_00e3ac54) ||
             (_DAT_00e44960 < static_cast<double>(sequenceDelta))) &&
            (lastCommittedSequence != currentReliableSequence)) {
            lastCommittedSequence = currentReliableSequence;
            lastCommittedTickMs = nowMs;
            FUN_00653a60();
        }
    }
}
