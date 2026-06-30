// 0x00653800
// TNL bitstream decoder for an optional extended packet payload.
//
// Protocol shape, as recovered from the decompiled control flow:
// - The first control bit gates the entire block.
// - If the first bit is clear, the function does nothing.
// - If the first bit is set, the function reads a second control bit.
//   - If the second bit is set, the packet state is marked with flag 0x08
//     and the function exits early.
//   - If the second bit is clear, the function reads four compressed unsigned
//     values from the bitstream and recomputes derived bounds/capacity fields.
// - If the reader runs past the declared bit limit while checking the control
//   prefix, the original code sets the overflow byte but still falls through
//   to the extended decode path. That quirk is preserved here.
//
// The exact semantic names of the decoded fields are not exposed by the JSON
// export, so the reconstruction keeps them conservative but meaningful.

#include <algorithm>
#include <cstdint>
#include <cmath>

extern float DAT_00E2E210; // scale factor used by the original binary

extern "C" std::uint32_t FUN_00652840(void);

#pragma pack(push, 1)
struct PacketUpdateState
{
    std::uint8_t pad0[0xB8];
    std::uint32_t controlFlags;      // +0xB8
    std::uint8_t pad1[0x18];         // +0xBC..+0xD3
    std::uint32_t minimumPrimary;    // +0xD4
    std::uint8_t pad2[0x04];         // +0xD8..+0xDB
    std::uint32_t minimumSecondary;  // +0xDC
    std::uint8_t pad3[0x04];         // +0xE0..+0xE3
    std::uint32_t rawField0;         // +0xE4, decoded payload value 1
    std::uint32_t rawField1;         // +0xE8, decoded payload value 2
    std::uint32_t rawField2;         // +0xEC, decoded payload value 3
    std::uint32_t rawField3;         // +0xF0, decoded payload value 4
    std::uint32_t padF4;             // +0xF4, unused by this function
    std::uint32_t scaledBudget;      // +0xF8, derived and clamped
    std::uint32_t selectedPrimary;   // +0xFC, derived maximum of primary axis

    // Helper recovered from 0x006538d0.
    //
    // The function selects the larger of:
    // - the freshly decoded value in rawField1 and the pre-existing minimumPrimary
    // - the freshly decoded value in rawField3 and the pre-existing minimumSecondary
    //
    // It then multiplies the two selected dimensions, applies the engine's
    // scale constant, rounds to an integer, and clamps the result to 0x400.
    void RecomputeDerivedMetrics()
    {
        const std::uint32_t primary = std::max(rawField1, minimumPrimary);
        const std::uint32_t secondary = std::max(rawField3, minimumSecondary);

        selectedPrimary = primary;

        const double area = static_cast<double>(primary) * static_cast<double>(secondary);
        std::uint32_t budget = static_cast<std::uint32_t>(std::lround(area * DAT_00E2E210));
        if (budget > 0x400u) {
            budget = 0x400u;
        }

        scaledBudget = budget;
    }
};

struct NetBitReader
{
    std::uint8_t pad0[0x0C];
    std::uint8_t* bitBuffer;     // +0x0C
    std::uint8_t pad1[0x08];     // +0x10..+0x17
    std::uint32_t bitCursor;     // +0x18, bit index
    std::uint8_t overflow;       // +0x1C, set when the reader runs out
    std::uint8_t pad2[0x0F];     // +0x1D..+0x2B
    std::uint32_t bitLimit;      // +0x2C, maximum valid bit index

    // Decode the optional packet block described above.
    // This is modeled as a normal x86 member function, i.e. `thiscall` at the
    // machine-code level.
    //
    // The stream is bit-addressed and read least-significant-bit first within
    // each byte, which matches the original `byte*(bitIndex >> 3)` /
    // `(1 << (bitIndex & 7))` test pattern in the decompilation.
    void DecodeOptionalExtendedBlock(PacketUpdateState* packetState)
    {
        const std::uint32_t firstBitIndex = bitCursor;

        if (bitLimit < firstBitIndex) {
            overflow = 1;
            return;
        }

        const std::uint8_t firstByte = bitBuffer[firstBitIndex >> 3];
        const std::uint32_t secondBitIndex = firstBitIndex + 1;
        bitCursor = secondBitIndex;

        if ((firstByte & (static_cast<std::uint8_t>(1u << (firstBitIndex & 7u)))) != 0) {
            if (bitLimit < secondBitIndex) {
                overflow = 1;
            } else {
                const std::uint8_t secondByte = bitBuffer[secondBitIndex >> 3];
                bitCursor = firstBitIndex + 2;

                if ((secondByte & (static_cast<std::uint8_t>(1u << (secondBitIndex & 7u)))) != 0) {
                    packetState->controlFlags |= 0x08u;
                    return;
                }
            }

            // Extended payload path:
            // four compressed unsigned values are read from the bitstream and
            // stored directly into the packet state. Only two of them are used
            // immediately; the remaining pair is preserved for later consumers.
            packetState->rawField0 = ReadPackedUnsignedFromStream();
            packetState->rawField1 = ReadPackedUnsignedFromStream();
            packetState->rawField2 = ReadPackedUnsignedFromStream();
            packetState->rawField3 = ReadPackedUnsignedFromStream();

            packetState->RecomputeDerivedMetrics();
        }
    }

private:
    static std::uint32_t ReadPackedUnsignedFromStream()
    {
        // 0x00652840: helper that reads a variable-width unsigned value from
        // the active bitstream. The exact width logic is reconstructed in the
        // binary export for that function and is intentionally kept separate.
        return FUN_00652840();
    }
};

#pragma pack(pop)
