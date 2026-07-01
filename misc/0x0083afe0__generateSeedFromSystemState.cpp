// FUNC_NAME: generateSeedFromSystemState
// Address: 0x0083afe0
// Role: Generates a seed value based on hashed constants and system entropy (two random sources).
// If the sum of four random measurements is less than 40, the low byte of the result is set to 1;
// otherwise, it is cleared. When either initial hash fails, returns a fallback based on the second hash.

#include <cstdint>

// Internal forward declarations (these are __cdecl free functions)
int     __cdecl getHashFromConstant(uint32_t seed);          // FUN_008e9cb0
int     __cdecl getRandomValueOne();                         // FUN_008ebfc0
int     __cdecl getRandomValueTwo();                         // FUN_008ec040

uint32_t generateSeedFromSystemState(void)
{
    int hash1 = getHashFromConstant(0x369ac561);
    uint32_t hash2 = getHashFromConstant(0xa5975eb2);

    // Only proceed if both hash results are non‑zero (e.g., system initialized)
    if (hash1 != 0 && hash2 != 0)
    {
        int valA = getRandomValueOne();
        int valB = getRandomValueTwo();
        int valC = getRandomValueOne();
        int valD = getRandomValueTwo();

        int sum = valD + valC + valA + valB;

        // Construct result: take upper 24 bits of sum, set low byte to 1
        uint32_t result = (sum & 0xFFFFFF00) | 0x01;

        if (sum < 40)
        {
            return result;
        }
    }

    // Fallback: return hash2 with low byte cleared
    return hash2 & 0xFFFFFF00;
}