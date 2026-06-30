// FUNC_NAME: getTerrainCellPointer
#include <cstdint>

// Global data tables from the binary (addresses from Ghidra)
extern uint8_t  g_byteLookupTable[]; // DAT_010beed0 - sparse index table
extern uint32_t g_baseOffset;        // DAT_01205530 - offset into lookupTable
extern float    g_worldOrigin;       // DAT_00e445e0 - world coordinate bias
extern uint8_t  g_cellData[];        // DAT_010c08f0 - 8‑byte cell records

// Returns a pointer to an 8‑byte cell structure for the given world coordinates.
// The first parameter (unused) is a relic of the calling convention.
void* __fastcall getTerrainCellPointer(void* /*unused*/, float* coords)
{
    // Convert world coordinates to grid indices (0-255)
    int gridX = static_cast<int>(coords[0] + g_worldOrigin) & 0xFF;
    int gridY = static_cast<int>(coords[1] + g_worldOrigin) & 0xFF;

    // The +1 & 0xFF ensures indices wrap around 256 (avoid zero?).
    int indexX = (gridX + 1) & 0xFF;
    int indexY = (gridY + 1) & 0xFF;

    // First lookup: get a byte from the table at (baseOffset + indexX)
    uint8_t innerByte = g_byteLookupTable[g_baseOffset + indexX];

    // Second lookup: index = baseOffset + indexY + innerByte (mod 256 implicit via array bounds)
    uint8_t finalByte = g_byteLookupTable[g_baseOffset + indexY + innerByte];

    // Each cell is 8 bytes, so multiply and add to base address.
    return reinterpret_cast<void*>(g_cellData + static_cast<uint32_t>(finalByte) * 8);
}