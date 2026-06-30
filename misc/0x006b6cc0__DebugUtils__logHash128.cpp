// FUNC_NAME: DebugUtils::logHash128
// Function address: 0x006b6cc0
// Computes a DJB2-style 32-bit hash from a 128-bit key (four uint32 components) and logs it.
// The hash uses the polynomial: (((comp[0]*33 + comp[1])*33 + comp[2])*33 + comp[3]
// Uses 64-bit arithmetic to avoid overflow, then truncates to 32 bits.
extern void __cdecl DebugLog(int logLevel, uint32_t value, uint32_t arg3, uint32_t arg4); // at 0x00814550

void __fastcall logHash128(const uint32_t components[4])
{
    uint64_t hash = components[0];
    hash = hash * 33 + components[1];
    hash = hash * 33 + components[2];
    hash = hash * 33 + components[3];
    
    uint32_t finalHash = (uint32_t)(hash & 0xFFFFFFFF);
    
    // Log with level 2 (likely debug/verbose), additional parameters unknown (always 1)
    DebugLog(2, finalHash, 1, 1);
}