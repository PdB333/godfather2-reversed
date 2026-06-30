// FUNC_NAME: buildEntityGUID
// Function at 0x51D730: Converts a 3-field ID struct (type, part1, part2) into a 64-bit packed GUID.
// Used by multiple entities to construct unique identifiers from type and two 32-bit parts.
// The struct layout: +0x00 type (uint), +0x04 part1 (uint), +0x08 part2 (uint).

#include <cstdint>

// Input structure for the packed ID
struct IdComponents {
    uint32_t type;   // +0x00
    uint32_t part1;  // +0x04
    uint32_t part2;  // +0x08
};

// Returns a 64-bit packed ID based on the type field.
// Cases:
//   0 -> 0
//   1,2,4 -> (part2 & 0xFFFF) << 32 | part1
//   3 -> (0x10000 | (part2 & 0xFFFF)) << 32 | part1
//   5 -> part1 (zero-extended to 64-bit)
//   7 -> 0x8000000000000000
//   default -> 0 (or part1 if type==5 path sets it)
uint64_t buildEntityGUID(void* in_EAX) {
    IdComponents* comps = (IdComponents*)in_EAX;
    uint32_t part1 = 0;
    uint32_t highWord = 0;

    switch (comps->type) {
    case 0:
        return 0;

    case 3:
        highWord = 0x10000;
        // fall through

    case 1:
    case 2:
    case 4:
        // Pack: high 32 bits = (highWord | (part2 & 0xFFFF)), low 32 bits = part1
        return (uint64_t)(highWord | (comps->part2 & 0xFFFF)) << 32 | comps->part1;

    case 5:
        part1 = comps->part1;
        // fall through to default returns part1

    default:
        return (uint64_t)part1;

    case 7:
        return 0x8000000000000000;
    }
}