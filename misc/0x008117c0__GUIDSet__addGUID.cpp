// FUNC_NAME: GUIDSet::addGUID
// Function at 0x008117c0: Adds a 128-bit GUID to a fixed-size array (max 4) if not already present and not an invalid sentinel.
// Param param_1: pointer to 4 ints = 128-bit GUID
// Param param_2: pointer to GUIDSet structure (first 16 bytes = array of 4 GUIDs, offset 0x10 = count uint32)
// Sentinels: {0xBABDB9BA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911} and {0,0,0,0} are considered invalid.
// Calls FUN_0088db10 to transform GUID (likely a hash or deduplication) before storing.

#include <cstdint>

struct GUIDSet {
    int32_t guids[4][4];   // 4 slots, each 4 ints (128-bit)
    uint32_t count;        // offset 0x10
};

void GUIDSet::addGUID(int32_t* guid128, GUIDSet* set) {
    int iVar1;

    // Check if GUID matches the invalid sentinel pattern
    if ( ( ( ( guid128[0] != -0x45245246 ) || ( guid128[1] != -0x41104111 ) ||
             ( guid128[2] != -0x153ea5ab ) || ( guid128[3] != -0x6eeff6ef ) ) &&
         ( ( guid128[0] != 0 ) || ( guid128[1] != 0 ) ||
           ( guid128[2] != 0 ) || ( guid128[3] != 0 ) ) ) )
    {
        // Transform the GUID (hash / deduplicate) via external function
        iVar1 = FUN_0088db10(guid128[0], guid128[1], guid128[2], guid128[3]);
        if (iVar1 != 0) {
            // If there's room, store the transformed value in the set
            if (set->count < 4) {
                set->guids[set->count][0] = iVar1; // Only first int stored? Or entire guid? Decompiled shows only 1 int stored.
                set->count++;
            }
        }
    }
    return;
}