// FUNC_NAME: randomRange
// Address: 0x006b9be0
// Role: Returns a pseudo-random integer in the range [minVal, maxVal) using a precomputed table of floats and a global counter.

#include <cstdint>

extern uint32_t g_randomCounter;        // DAT_012054b4
extern const uint32_t g_tableMask;      // DAT_010c2678
extern const float g_randomTable[];     // DAT_010c2680

uint32_t randomRange(uint32_t minVal, uint32_t maxVal) {
    if (minVal < maxVal) {
        uint32_t tableIndex = g_tableMask & g_randomCounter;
        g_randomCounter++;

        float range = static_cast<float>(static_cast<int>(maxVal - minVal));
        // ROUND to nearest integer (simulated by adding 0.5f and truncating)
        int32_t offset = static_cast<int32_t>(range * g_randomTable[tableIndex] + 0.5f);
        return minVal + static_cast<uint32_t>(offset);
    }
    return minVal;
}