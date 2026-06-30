// FUNC_NAME: Random::getRandomPair
// Address: 0x00673510
// Role: Retrieves a pair of random values; if the single-value flag (offset 0x1c) is set, only the first value is generated and the second is forced to zero.

#include <cstdint>

void Random::getRandomPair(int32_t* outValue1, int32_t* outValue2) {
    int32_t first = getNextRandom(); // FUN_00676010
    if (*(reinterpret_cast<int32_t*>(this + 0x1c)) == 0) {
        int32_t second = getNextRandom(); // second call
        *outValue1 = first;
        *outValue2 = second;
    } else {
        *outValue1 = first;
        *outValue2 = 0;
    }
}