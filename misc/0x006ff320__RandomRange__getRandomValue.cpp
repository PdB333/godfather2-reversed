// FUNC_NAME: RandomRange::getRandomValue
// Address: 0x006ff320
// Returns a random float uniformly distributed between min and max stored at +0xFC and +0x100.

class RandomRange {
public:
    // +0xFC
    float minVal;
    // +0x100
    float maxVal;
};

// Global constant: 1.0f / RAND_MAX  (assumed RAND_MAX = 32767)
extern float g_invRandMax; // at DAT_00e44590

float __fastcall RandomRange::getRandomValue(void* thisPtr) {
    int randInt = rand();
    float range = thisPtr->maxVal - thisPtr->minVal;
    return ((float)randInt * g_invRandMax) * range + thisPtr->minVal;
}