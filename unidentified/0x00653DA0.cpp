// 0x00653DA0 - TNLConnection::ComputeOutboundWindowState()
//
// This member evaluates the outbound reliable-sequence window for the TNL
// networking layer. The result is used by the packet send loop as a coarse
// "is the connection under back-pressure?" gate.
//
// Protocol notes:
// - `nextSendSequence` at +0x98 advances as the game prepares outbound packets.
// - `oldestUnackedSequence` at +0x94 marks the earliest still-relevant packet.
// - The difference is compared against a 32-slot sequence ring. A gap above
//   29 packets is treated as window pressure and the low byte is forced to 1.
// - In throttled modes (`modeFlags & 0x0C`), the raw sequence gap is converted
//   to float and compared against a per-connection timing threshold at +0x1B8.
// - Callers only test truthiness in most places, but the packed return value
//   keeps the coarse sequence gap in the upper bytes for debugging / telemetry.

#include <cstdint>

extern float DAT_00e44578;

struct TNLConnection
{
    std::uint8_t _pad_00[0x94];
    std::uint32_t oldestUnackedSequence;   // 0x94
    std::uint32_t nextSendSequence;        // 0x98
    std::uint8_t _pad_9c[0x1c];
    std::uint8_t modeFlags;                // 0xB8
    std::uint8_t _pad_b9[0x1b8 - 0xb9];
    float packetThrottleThreshold;         // 0x1B8

    std::uint32_t __thiscall ComputeOutboundWindowState() const;
};

std::uint32_t __thiscall TNLConnection::ComputeOutboundWindowState() const
{
    // Sequence distance between the newest outbound packet and the oldest
    // packet that has not yet been acknowledged by the peer.
    const std::int32_t sequenceGap =
        static_cast<std::int32_t>(nextSendSequence) - static_cast<std::int32_t>(oldestUnackedSequence);

    // Preserve the packed status word shape seen in the original binary:
    // the upper bytes carry the coarse gap, while the low byte becomes a
    // non-zero marker when the window has crossed the hard pressure limit.
    const std::uint32_t packedGap = static_cast<std::uint32_t>(sequenceGap) & 0xffffff00u;

    // Hard back-pressure threshold.
    // The send window is effectively 32 entries wide, and the game treats a
    // gap above 29 packets as "too far ahead" even before wrap-around risk.
    if (sequenceGap > 0x1d) {
        return packedGap | 1u;
    }

    // Throttled transport modes use a timing-based gate instead of the simple
    // sequence-gap test. The decompiler shows a signed-to-float compensation
    // constant here; it is preserved verbatim to match the original semantics.
    if ((modeFlags & 0x0c) != 0) {
        float gapAsFloat = static_cast<float>(sequenceGap);
        if (sequenceGap < 0) {
            gapAsFloat += DAT_00e44578;
        }

        return (packetThrottleThreshold <= gapAsFloat) ? 1u : 0u;
    }

    // Non-throttled mode: return the coarse packed window state directly.
    return packedGap;
}
