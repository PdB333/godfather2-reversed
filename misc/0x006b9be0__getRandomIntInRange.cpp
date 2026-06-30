// FUNC_NAME: getRandomIntInRange

#include <cmath>

// Global random state variables
static uint32_t randomMask = DAT_010c2678;        // +0x010c2678
static uint32_t randomCounter = DAT_012054b4;     // +0x012054b4
static float randomTable[] = { /* values at DAT_010c2680 */ }; // +0x010c2680
static const float floatTwoPower32 = DAT_00e44578; // +0x00e44578 (likely 4294967296.0f)

/**
 * Returns a random integer in the range [min, max) if min < max, otherwise returns min.
 * Uses a simple LCG-like generator with a precomputed table of uniform floats.
 */
uint32_t getRandomIntInRange(uint32_t min, uint32_t max)
{
    if (min < max)
    {
        // Select a random float from the table using the current counter masked
        uint32_t index = randomMask & randomCounter;
        ++randomCounter;

        // Compute range as float; handle potential unsigned wrap as negative signed
        float rangeFloat = static_cast<float>(static_cast<int32_t>(max - min));
        if (static_cast<int32_t>(max - min) < 0)
        {
            rangeFloat += floatTwoPower32; // Adjust for unsigned overflow
        }

        // Scale the random float by the range and round to nearest integer
        int32_t offset = static_cast<int32_t>(llround(rangeFloat * randomTable[index]));

        return min + offset;
    }
    return min;
}