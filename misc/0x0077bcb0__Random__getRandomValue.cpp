// FUNC_NAME: Random::getRandomValue
// Function address: 0x0077bcb0
// Computes a random float in a range defined by parameters stored in a sub-object.
// The sub-object at this+8 contains two floats: base value at +0x64 and half-range at +0x68.
// The formula: base + halfRange * (rand() * constant1 * constant2 - 1.0f)
// Constants are global floats.

#include <cstdlib>

class Random {
public:
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: pointer to RandomParams
    // +0x0C: ...
    
    struct RandomParams {
        // +0x64: base value (fVar1)
        float base;
        // +0x68: half-range (fVar3)
        float halfRange;
    };

    // Returns a random float in the range [base - halfRange, base + halfRange * (RAND_MAX * constants - 1)]
    // The exact range depends on the global constants.
    double getRandomValue() const;
};

extern float DAT_00e44590;  // scaling factor 1
extern float DAT_00d5eee4;  // scaling factor 2
extern float DAT_00d5780c;  // default return value when no params

double Random::getRandomValue() const {
    RandomParams* params = *(RandomParams**)(this + 8);
    if (params != nullptr) {
        float base = params->base;          // +0x64
        float halfRange = params->halfRange; // +0x68
        float scaledRange = halfRange * base;
        int randVal = rand();
        // Compute: base + scaledRange * (rand() * constants - 1)
        return (double)(((float)randVal * DAT_00e44590 * scaledRange * DAT_00d5eee4 + base) - scaledRange);
    }
    return (double)DAT_00d5780c;
}