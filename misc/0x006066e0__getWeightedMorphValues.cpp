// FUNC_NAME: getWeightedMorphValues
// Address: 0x006066e0
// Role: Looks up two 16-bit values from a morph weight table (indexed by ID) and optionally shifts them by a LOD factor.
// The table has entries of size 0x38 bytes. If bit0 at offset 0x0C is set, the values are right-shifted by (lodLevel & 0x1F) with a floor of 1.
// Otherwise the raw values are used.

#include <stdint.h>

// Structure of each entry in the morph weight table (size 0x38)
struct MorphWeightEntry
{
    // +0x00: unknown (4 bytes? but we only use offsets)
    // +0x02: first weight (uint16)
    // +0x04: second weight (uint16)
    // +0x0C: flags (bit0 = apply shift)
    uint8_t _pad0[2];
    uint16_t weight1;   // +0x02
    uint16_t weight2;   // +0x04
    uint8_t _pad1[6];
    uint8_t flags;      // +0x0C
    // remaining bytes to reach 0x38
} __attribute__((packed));

// Global table at 0x011a0f28, 0x1000 entries
static MorphWeightEntry* const s_morphWeightTable = (MorphWeightEntry*)0x011a0f28;
static const uint32_t kMaxMorphEntries = 0x1000;

// The function as reconstructed from the assembly:
// Parameter 1 (in EAX): morph ID (index)
// Parameter 2 (byte on stack): lod level (shift amount, bits 0-4 only)
// Output pointer 1 (in ESI): receives weight1 (possibly shifted)
// Output pointer 2 (in EDI): receives weight2 (possibly shifted)
void __cdecl getWeightedMorphValues(uint32_t morphId, uint8_t lodLevel, uint16_t* outWeight1, uint16_t* outWeight2)
{
    MorphWeightEntry* entry = nullptr;

    if (morphId < kMaxMorphEntries)
    {
        entry = &s_morphWeightTable[morphId];
    }
    else
    {
        // Invalid index – set outputs to 0 (the original binary would crash here,
        // but we add a safe guard for the reconstruction)
        *outWeight1 = 0;
        *outWeight2 = 0;
        return;
    }

    if (entry->flags & 1) // bit0 indicates "use LOD shift"
    {
        uint16_t shifted1 = entry->weight1 >> (lodLevel & 0x1F);
        if (shifted1 == 0)
            shifted1 = 1;
        *outWeight1 = shifted1;

        uint16_t shifted2 = entry->weight2 >> (lodLevel & 0x1F);
        if (shifted2 == 0)
            shifted2 = 1;
        *outWeight2 = shifted2;
    }
    else
    {
        *outWeight1 = entry->weight1;
        *outWeight2 = entry->weight2;
    }
}