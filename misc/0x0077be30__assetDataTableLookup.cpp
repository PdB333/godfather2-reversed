// FUNC_NAME: assetDataTableLookup
// Returns a 32-bit value from a global lookup table at DAT_00e51d68.
// The table has entries of size 0xC (12 bytes) each, indexed by param_1.
// The first DWORD of each entry is returned.
// Used by FUN_0077a910 which likely loads asset data.

uint32_t assetDataTableLookup(int index)
{
    // Global table base: DAT_00e51d68
    // Each entry is 0xC bytes: [uint32 value, uint32 unknown1, uint32 unknown2]
    return *(uint32_t *)(DAT_00e51d68 + index * 0xC);
}